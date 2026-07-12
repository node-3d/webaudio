#include "audio-setting.hpp"
#include "audio-context.hpp"


IMPLEMENT_ES5_CLASS(AudioSetting);

void AudioSetting::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(value);
	JS_ASSIGN_METHOD(cancelAndHoldAtTime);
	JS_ASSIGN_METHOD(cancelScheduledValues);
	JS_ASSIGN_METHOD(setValueCurveAtTime);
	JS_ASSIGN_METHOD(setTargetAtTime);
	JS_ASSIGN_METHOD(exponentialRampToValueAtTime);
	JS_ASSIGN_METHOD(linearRampToValueAtTime);
	JS_ASSIGN_METHOD(setValueAtTime);
	JS_ASSIGN_GETTER(maxValue);
	JS_ASSIGN_GETTER(minValue);
	JS_ASSIGN_GETTER(defaultValue);
	JS_ASSIGN_METHOD(destroy);

	exports.Set("AudioSetting", ctor);
}


bool AudioSetting::isAudioSetting(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


AudioSetting::AudioSetting(const Napi::CallbackInfo &info) : CommonSetting(info.This(), "AudioSetting") {
	NAPI_ENV;
	super(info);

	Napi::Object context = info[0].As<Napi::Object>();
	Napi::External<void> extSetting = info[1].As<Napi::External<void>>();

	SettingPtr *setting = reinterpret_cast<SettingPtr *>(extSetting.Data());

	reset(context, *setting);
}


AudioSetting::~AudioSetting() {
	_destroy();
}


void AudioSetting::_destroy() {
	DES_CHECK;
	CommonSetting::_destroy();
}


JS_IMPLEMENT_METHOD(AudioSetting, setValueAtTime) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, value);

	_impl->setFloat(value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioSetting, linearRampToValueAtTime) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, value);

	_impl->setFloat(value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioSetting, exponentialRampToValueAtTime) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, value);

	_impl->setFloat(value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioSetting, setTargetAtTime) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, target);

	_impl->setFloat(target);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioSetting, setValueCurveAtTime) {
	THIS_CHECK;
	REQ_ARRAY_ARG(0, values);
	// TODO: read values[0]

	_impl->setFloat(values.Get(0U).ToNumber().FloatValue());
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioSetting, cancelScheduledValues) {
	THIS_CHECK;
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioSetting, cancelAndHoldAtTime) {
	THIS_CHECK;
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(AudioSetting, value) {
	THIS_CHECK;
	Napi::Object context = _context.Value();
	AudioContext *audioContext = AudioContext::unwrap(context);
	lab::ContextRenderLock renderLock(audioContext->getCtx().get(), "AudioSetting::valueGetter");

	RET_NUM(_impl->valueFloat());
}

JS_IMPLEMENT_SETTER(AudioSetting, value) {
	THIS_CHECK;
	SETTER_FLOAT_ARG;
	_impl->setFloat(v);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(AudioSetting, defaultValue) {
	THIS_CHECK;
	RET_NUM(0);
}


JS_IMPLEMENT_GETTER(AudioSetting, minValue) {
	THIS_CHECK;
	RET_NUM(0);
}


JS_IMPLEMENT_GETTER(AudioSetting, maxValue) {
	THIS_CHECK;
	RET_NUM(1);
}


JS_IMPLEMENT_METHOD(AudioSetting, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
