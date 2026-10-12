#include "audio-buffer.hpp"
#include "audio-context.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <new>
#include <string>

IMPLEMENT_ES5_CLASS(AudioBuffer);

namespace {
void domError(Napi::Env env, const char *message, const char *name) {
	Napi::Function ctor = env.Global().Get("DOMException").As<Napi::Function>();
	napi_value args[] = { Napi::String::New(env, message), Napi::String::New(env, name) };
	napi_throw(env, ctor.New(2, args));
}

bool unsignedArg(Napi::Env env, Napi::Value value, const char *name, uint32_t &result) {
	if (!value.IsNumber()) {
		Napi::TypeError::New(env, std::string(name) + " must be a number").ThrowAsJavaScriptException();
		return false;
	}
	double n = value.As<Napi::Number>().DoubleValue();
	if (!std::isfinite(n) || n < 0 || n > std::numeric_limits<uint32_t>::max() || std::trunc(n) != n) {
		domError(env, "Value is outside its nominal range", "NotSupportedError");
		return false;
	}
	result = static_cast<uint32_t>(n);
	return true;
}

bool rateArg(Napi::Env env, Napi::Value value, float &result) {
	if (!value.IsNumber()) {
		Napi::TypeError::New(env, "sampleRate must be a number").ThrowAsJavaScriptException();
		return false;
	}
	double n = value.As<Napi::Number>().DoubleValue();
	if (!std::isfinite(n) || n < 3000 || n > 768000) {
		domError(env, "sampleRate is outside the supported range", "NotSupportedError");
		return false;
	}
	result = static_cast<float>(n);
	return true;
}
} // namespace

void AudioBuffer::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(copyToChannel);
	JS_ASSIGN_METHOD(copyFromChannel);
	JS_ASSIGN_METHOD(getChannelData);
	JS_ASSIGN_GETTER(numberOfChannels);
	JS_ASSIGN_GETTER(sampleRate);
	JS_ASSIGN_GETTER(duration);
	JS_ASSIGN_GETTER(length);
	JS_ASSIGN_METHOD(destroy);
	exports.Set("AudioBuffer", ctor);
}

AudioBuffer::AudioBuffer(const Napi::CallbackInfo &info) : CommonBus(info.This(), "AudioBuffer") {
	NAPI_ENV;
	super(info);
	if (info.Length() == 2 && info[1].IsExternal()) {
		if (!info[0].IsObject()) {
			Napi::TypeError::New(env, "Invalid decoded AudioBuffer context").ThrowAsJavaScriptException();
			return;
		}
		BusPtr *bus = static_cast<BusPtr *>(info[1].As<Napi::External<void>>().Data());
		if (!bus || !*bus) {
			Napi::TypeError::New(env, "Invalid decoded AudioBuffer data").ThrowAsJavaScriptException();
			return;
		}
		reset(info[0].As<Napi::Object>(), *bus);
	} else {
		if (info.Length() != 1 || !info[0].IsObject()) {
			Napi::TypeError::New(env, "AudioBuffer requires an options object").ThrowAsJavaScriptException();
			return;
		}
		Napi::Object options = info[0].As<Napi::Object>();
		if (!options.Has("length") || !options.Has("sampleRate")) {
			Napi::TypeError::New(env, "length and sampleRate are required").ThrowAsJavaScriptException();
			return;
		}
		uint32_t channels = 1, length = 0;
		float rate = 0;
		if (options.Has("numberOfChannels") &&
		    !unsignedArg(env, options.Get("numberOfChannels"), "numberOfChannels", channels))
			return;
		if (!unsignedArg(env, options.Get("length"), "length", length) ||
		    !rateArg(env, options.Get("sampleRate"), rate))
			return;
		if (channels < 1 || channels > 32 || length < 1 ||
		    length > static_cast<uint32_t>(std::numeric_limits<int>::max())) {
			domError(env, "AudioBuffer dimensions are outside their nominal range", "NotSupportedError");
			return;
		}
		if (static_cast<uint64_t>(channels) * length > std::numeric_limits<size_t>::max() / sizeof(float)) {
			Napi::RangeError::New(env, "AudioBuffer is too large").ThrowAsJavaScriptException();
			return;
		}
		try {
			_impl = std::make_shared<lab::AudioBus>(static_cast<int>(channels), static_cast<int>(length));
			_impl->setSampleRate(rate);
		} catch (const std::bad_alloc &) {
			Napi::RangeError::New(env, "Unable to allocate AudioBuffer").ThrowAsJavaScriptException();
			return;
		}
	}
	_channelData.resize(_impl->numberOfChannels());
}

AudioBuffer::~AudioBuffer() {
	_destroy();
}

void AudioBuffer::_destroy() {
	DES_CHECK;
	for (auto &channel : _channelData)
		channel.Reset();
	CommonBus::_destroy();
}

BusPtr AudioBuffer::snapshotBus() {
	BusPtr copy = std::make_shared<lab::AudioBus>(_impl->numberOfChannels(), _impl->length());
	copy->setSampleRate(_impl->sampleRate());
	for (size_t i = 0; i < _channelData.size(); ++i) {
		if (!_channelData[i].IsEmpty()) {
			Napi::Float32Array view = _channelData[i].Value();
			float *storage = _impl->channel(static_cast<int>(i))->mutableData();
			if (view.ArrayBuffer().IsDetached()) {
				std::memset(storage, 0, static_cast<size_t>(_impl->length()) * sizeof(float));
			} else {
				std::memcpy(storage, view.Data(), static_cast<size_t>(_impl->length()) * sizeof(float));
				view.ArrayBuffer().Detach();
			}
			_channelData[i].Reset();
		}
		std::memcpy(
		    copy->channel(static_cast<int>(i))->mutableData(),
		    _impl->channel(static_cast<int>(i))->data(),
		    static_cast<size_t>(_impl->length()) * sizeof(float)
		);
	}
	return copy;
}

JS_IMPLEMENT_METHOD(AudioBuffer, getChannelData) {
	THIS_CHECK;
	if (info.Length() < 1) {
		Napi::TypeError::New(env, "A channel index is required").ThrowAsJavaScriptException();
		RET_UNDEFINED;
	}
	uint32_t index;
	if (!unsignedArg(env, info[0], "channel", index))
		RET_UNDEFINED;
	if (index >= static_cast<uint32_t>(_impl->numberOfChannels())) {
		domError(env, "Channel index is out of range", "IndexSizeError");
		RET_UNDEFINED;
	}
	if (!_channelData[index].IsEmpty() && _channelData[index].Value().ArrayBuffer().IsDetached())
		_channelData[index].Reset();
	if (_channelData[index].IsEmpty()) {
		Napi::Float32Array data = Napi::Float32Array::New(env, _impl->length());
		std::memcpy(
		    data.Data(), _impl->channel(index)->data(), static_cast<size_t>(_impl->length()) * sizeof(float)
		);
		_channelData[index] = Napi::Persistent(data);
	}
	RET_VALUE(_channelData[index].Value());
}

JS_IMPLEMENT_METHOD(AudioBuffer, copyFromChannel) {
	THIS_CHECK;
	if (info.Length() < 2 || !info[0].IsTypedArray() ||
	    info[0].As<Napi::TypedArray>().TypedArrayType() != napi_float32_array) {
		Napi::TypeError::New(env, "destination must be a Float32Array").ThrowAsJavaScriptException();
		RET_UNDEFINED;
	}
	uint32_t index;
	if (!unsignedArg(env, info[1], "channel", index))
		RET_UNDEFINED;
	if (index >= static_cast<uint32_t>(_impl->numberOfChannels())) {
		domError(env, "Channel index is out of range", "IndexSizeError");
		RET_UNDEFINED;
	}
	uint32_t offset = 0;
	if (info.Length() > 2 && !unsignedArg(env, info[2], "bufferOffset", offset))
		RET_UNDEFINED;
	if (!_channelData[index].IsEmpty() && _channelData[index].Value().ArrayBuffer().IsDetached()) {
		domError(env, "Channel data was detached", "UnknownError");
		RET_UNDEFINED;
	}
	Napi::Float32Array dest = info[0].As<Napi::Float32Array>();
	const float *source =
	    _channelData[index].IsEmpty() ? _impl->channel(index)->data() : _channelData[index].Value().Data();
	if (offset < static_cast<uint32_t>(_impl->length())) {
		size_t count = std::min(dest.ElementLength(), static_cast<size_t>(_impl->length() - offset));
		if (count > 0)
			std::memmove(dest.Data(), source + offset, count * sizeof(float));
	}
	RET_UNDEFINED;
}

JS_IMPLEMENT_METHOD(AudioBuffer, copyToChannel) {
	THIS_CHECK;
	if (info.Length() < 2 || !info[0].IsTypedArray() ||
	    info[0].As<Napi::TypedArray>().TypedArrayType() != napi_float32_array) {
		Napi::TypeError::New(env, "source must be a Float32Array").ThrowAsJavaScriptException();
		RET_UNDEFINED;
	}
	uint32_t index;
	if (!unsignedArg(env, info[1], "channel", index))
		RET_UNDEFINED;
	if (index >= static_cast<uint32_t>(_impl->numberOfChannels())) {
		domError(env, "Channel index is out of range", "IndexSizeError");
		RET_UNDEFINED;
	}
	uint32_t offset = 0;
	if (info.Length() > 2 && !unsignedArg(env, info[2], "bufferOffset", offset))
		RET_UNDEFINED;
	if (!_channelData[index].IsEmpty() && _channelData[index].Value().ArrayBuffer().IsDetached()) {
		domError(env, "Channel data was detached", "UnknownError");
		RET_UNDEFINED;
	}
	Napi::Float32Array source = info[0].As<Napi::Float32Array>();
	float *dest = _channelData[index].IsEmpty() ? _impl->channel(index)->mutableData()
	                                            : _channelData[index].Value().Data();
	if (offset < static_cast<uint32_t>(_impl->length())) {
		size_t count = std::min(source.ElementLength(), static_cast<size_t>(_impl->length() - offset));
		if (count > 0)
			std::memmove(dest + offset, source.Data(), count * sizeof(float));
	}
	RET_UNDEFINED;
}

JS_IMPLEMENT_GETTER(AudioBuffer, length) {
	THIS_CHECK;
	RET_NUM(_impl->length());
}
JS_IMPLEMENT_GETTER(AudioBuffer, duration) {
	THIS_CHECK;
	RET_NUM(static_cast<double>(_impl->length()) / _impl->sampleRate());
}
JS_IMPLEMENT_GETTER(AudioBuffer, sampleRate) {
	THIS_CHECK;
	RET_NUM(_impl->sampleRate());
}
JS_IMPLEMENT_GETTER(AudioBuffer, numberOfChannels) {
	THIS_CHECK;
	RET_NUM(_impl->numberOfChannels());
}

JS_IMPLEMENT_METHOD(AudioBuffer, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
