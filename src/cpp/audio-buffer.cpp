#include "audio-buffer.hpp"
#include "audio-context.hpp"


IMPLEMENT_ES5_CLASS(AudioBuffer);

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

	Napi::Object context = info[0].As<Napi::Object>();

	if (info.Length() > 1) {
		Napi::External<void> extBus = info[1].As<Napi::External<void>>();
		BusPtr *busPtr = reinterpret_cast<BusPtr *>(extBus.Data());
		reset(context, *busPtr);
	} else {
		BusPtr bus = std::make_shared<lab::AudioBus>(1, 1, false);
		reset(context, bus);
	}
}


AudioBuffer::~AudioBuffer() {
	_destroy();
}


void AudioBuffer::_destroy() {
	DES_CHECK;
	CommonBus::_destroy();
}


JS_IMPLEMENT_METHOD(AudioBuffer, getChannelData) {
	THIS_CHECK;
	REQ_UINT32_ARG(0, channelIndex);

	// TODO: do something?
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioBuffer, copyFromChannel) {
	THIS_CHECK;
	REQ_OBJ_ARG(0, destination);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);

	// TODO: do something?
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioBuffer, copyToChannel) {
	THIS_CHECK;
	REQ_OBJ_ARG(0, source);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);

	// TODO: do something?
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(AudioBuffer, length) {
	THIS_CHECK;
	RET_NUM(_length);
}


JS_IMPLEMENT_GETTER(AudioBuffer, duration) {
	THIS_CHECK;
	RET_NUM(_duration);
}


JS_IMPLEMENT_GETTER(AudioBuffer, sampleRate) {
	THIS_CHECK;
	RET_NUM(_sampleRate);
}


JS_IMPLEMENT_GETTER(AudioBuffer, numberOfChannels) {
	THIS_CHECK;
	RET_NUM(_numberOfChannels);
}


JS_IMPLEMENT_METHOD(AudioBuffer, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
