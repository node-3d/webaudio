#include <LabSound/backends/AudioDevice_RtAudio.h>

#include "base-audio-context.hpp"


static inline float useSampleRate(float sampleRate, const lab::AudioDeviceInfo &info) {
	if (sampleRate <= 0.f) {
		return info.nominal_samplerate;
	}

	const auto &supported = info.supported_samplerates;
	bool isFound = std::find(supported.begin(), supported.end(), sampleRate) != supported.end();
	return isFound ? sampleRate : info.nominal_samplerate;
}

// Returns { input, output }
static inline std::pair<lab::AudioStreamConfig, lab::AudioStreamConfig>
getAudioConfig(bool hasInput, float sampleRate) {
	const std::vector<lab::AudioDeviceInfo> audioDevices = lab::AudioDevice_RtAudio::MakeAudioDeviceList();
	lab::AudioDeviceInfo defaultOutputInfo, defaultInputInfo;
	for (auto &info : audioDevices) {
		if (info.is_default_output) {
			defaultOutputInfo = info;
		} else if (info.is_default_input) {
			defaultInputInfo = info;
		}
	}

	lab::AudioStreamConfig outputConfig;
	if (defaultOutputInfo.index != -1) {
		outputConfig.device_index = defaultOutputInfo.index;
		outputConfig.desired_channels = std::min(2U, defaultOutputInfo.num_output_channels);
		outputConfig.desired_samplerate = useSampleRate(sampleRate, defaultOutputInfo);
	}

	lab::AudioStreamConfig inputConfig;
	if (hasInput) {
		if (defaultInputInfo.index != -1) {
			inputConfig.device_index = defaultInputInfo.index;
			inputConfig.desired_channels = std::min(1U, defaultInputInfo.num_input_channels);
			inputConfig.desired_samplerate = useSampleRate(sampleRate, defaultInputInfo);
		} else {
			throw std::invalid_argument("the default audio input device was requested but none were found");
		}
	}

	// RtAudio needs matching sample rates on input and output.
	// The optional user-defined rate has already been accounted for.
	if (hasInput && inputConfig.desired_samplerate != outputConfig.desired_samplerate) {
		float min_rate = std::min(inputConfig.desired_samplerate, outputConfig.desired_samplerate);
		inputConfig.desired_samplerate = min_rate;
		outputConfig.desired_samplerate = min_rate;
	}

	return { inputConfig, outputConfig };
}


bool compareMagic(const uint8_t *data, const int16_t *magic) {
	for (int i = 0; magic[i] != -2; i++) {
		if (magic[i] >= 0 && data[i] != magic[i]) {
			return false;
		}
	}
	return true;
}

std::string getExtension(const uint8_t *data) {
	static const int16_t wv[] = { 'w', 'v', 'p', 'k', -2 };
	static const int16_t wav[] = { 0x52, 0x49, 0x46, 0x46, -1, -1, -1, -1, 0x57, 0x41, 0x56, 0x45, -2 };
	static const int16_t flac[] = { 0x66, 0x4C, 0x61, 0x43, -2 };
	static const int16_t pat[] = { 0x47, 0x50, 0x41, 0x54, -2 };
	static const int16_t mid[] = { 0x4D, 0x54, 0x68, 0x64, -2 };
	static const int16_t opus[] = { 'O', 'p', 'u', 's', 'H', 'e', 'a', 'd', -2 };
	static const int16_t ogg[] = { 0x4F, 0x67, 0x67, 0x53, 0x00, 0x02, 0x00, 0x00, -2 };

	static const int16_t *numbers[] = { wv, wav, flac, pat, mid, opus, ogg, nullptr };
	static const char *extensions[] = { "wv", "wav", "flac", "pat", "mid", "opus", "ogg" };

	for (int i = 0; numbers[i] != nullptr; i++) {
		if (compareMagic(data, numbers[i])) {
			return extensions[i];
		}
	}

	return "";
}


IMPLEMENT_ES5_CLASS(BaseAudioContext);

void BaseAudioContext::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(_initListener);
	JS_ASSIGN_METHOD(resume);
	JS_ASSIGN_METHOD(decodeAudioData);
	JS_ASSIGN_METHOD(update);
	JS_ASSIGN_GETTER(state);
	JS_ASSIGN_GETTER(listener);
	JS_ASSIGN_GETTER(sampleRate);
	JS_ASSIGN_GETTER(currentTime);
	JS_ASSIGN_GETTER(destination);
	JS_ASSIGN_METHOD(destroy);

	exports.Set("BaseAudioContext", ctor);
}


BaseAudioContext::BaseAudioContext(const Napi::CallbackInfo &info)
    : CommonCtx(info.This(), "BaseAudioContext") {
	NAPI_ENV;
	super(info);

	Napi::External<void> extCtx = info[0].As<Napi::External<void>>();

	CtxPtr *ctx = reinterpret_cast<CtxPtr *>(extCtx.Data());
	reset(*ctx);

	_state = "running";
}


BaseAudioContext::~BaseAudioContext() {
	_destroy();
}


void BaseAudioContext::_destroy() {
	DES_CHECK;
	if (_state != "closed") {
		_state = "closed";
	}

	CommonCtx::_destroy();
}


JS_IMPLEMENT_METHOD(BaseAudioContext, _initListener) {
	THIS_CHECK;
	REQ_FUN_ARG(0, destinationCtor);
	REQ_FUN_ARG(1, listenerCtor);
	LET_FLOAT_ARG(2, sampleRate);
	Napi::Object context = info.This().As<Napi::Object>();

	napi_value argv[2];
	argv[0] = context;

	const auto config = getAudioConfig(false, sampleRate);
	auto device = std::make_shared<lab::AudioDevice_RtAudio>(config.first, config.second);

	auto destinationNode = std::make_shared<lab::AudioDestinationNode>(*_impl.get(), device);
	argv[1] = JS_EXT(&destinationNode);
	_destination.Reset(destinationCtor.New(2, argv), 1);

	ListenerPtr listener = _impl->listener();
	argv[1] = JS_EXT(&listener);
	_listener.Reset(listenerCtor.New(2, argv), 1);

	device->setDestinationNode(destinationNode);
	_impl->setDestinationNode(destinationNode);

	Napi::Function ctor = _ctorEs5.Value().As<Napi::Function>();
	Napi::String hrtf = ctor.Get("hrtf").As<Napi::String>();
	_impl->loadHrtfDatabase(hrtf);

	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(BaseAudioContext, decodeAudioData) {
	THIS_CHECK;
	REQ_OBJ_ARG(0, audioData);
	REQ_FUN_ARG(1, successCallback);
	REQ_FUN_ARG(2, bufferCtor);

	Napi::Object context = info.This().As<Napi::Object>();

	int len;
	const uint8_t *data = getArrayData(env, audioData, &len);

	std::vector<uint8_t> dataVec(data, data + len);

	std::string ext = getExtension(data);

	BusPtr bus = lab::MakeBusFromMemory(dataVec, ext, false);

	napi_value argv[2];
	argv[0] = context;

	argv[1] = JS_EXT(&bus);
	Napi::Object buffer = bufferCtor.New(2, argv);

	argv[0] = buffer;
	successCallback.Call(1, argv);

	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(BaseAudioContext, update) {
	THIS_CHECK;
	if (!_isDestroyed) {
		_impl->dispatchEvents();
	}
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(BaseAudioContext, resume) {
	THIS_CHECK;
	// TODO: do something?
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(BaseAudioContext, destination) {
	THIS_CHECK;
	RET_VALUE(_destination.Value());
}


JS_IMPLEMENT_GETTER(BaseAudioContext, currentTime) {
	THIS_CHECK;
	RET_NUM(_impl->currentTime());
}


JS_IMPLEMENT_GETTER(BaseAudioContext, sampleRate) {
	THIS_CHECK;
	RET_NUM(_impl->sampleRate());
}


JS_IMPLEMENT_GETTER(BaseAudioContext, listener) {
	THIS_CHECK;
	RET_VALUE(_listener.Value());
}


JS_IMPLEMENT_GETTER(BaseAudioContext, state) {
	THIS_CHECK;
	RET_STR(_state);
}


JS_IMPLEMENT_METHOD(BaseAudioContext, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
