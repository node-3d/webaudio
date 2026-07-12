#include "audio-param.hpp"
#include "audio-context.hpp"


IMPLEMENT_ES5_CLASS(AudioParam);

void AudioParam::init(Napi::Env env, Napi::Object exports) {
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

	exports.Set("AudioParam", ctor);
}


bool AudioParam::isAudioParam(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


AudioParam::AudioParam(const Napi::CallbackInfo &info) : CommonParam(info.This(), "AudioParam") {
	NAPI_ENV;
	super(info);

	Napi::Object context = info[0].As<Napi::Object>();
	Napi::External<void> extParam = info[1].As<Napi::External<void>>();

	ParamPtr *param = reinterpret_cast<ParamPtr *>(extParam.Data());

	reset(context, *param);
}


AudioParam::~AudioParam() {
	_destroy();
}


void AudioParam::_destroy() {
	DES_CHECK;
	CommonParam::_destroy();
}


JS_IMPLEMENT_METHOD(AudioParam, setValueAtTime) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);

	_impl->setValueAtTime(value, time);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioParam, linearRampToValueAtTime) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);

	_impl->linearRampToValueAtTime(value, time);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioParam, exponentialRampToValueAtTime) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, value);
	REQ_FLOAT_ARG(1, time);

	_impl->exponentialRampToValueAtTime(value, time);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioParam, setTargetAtTime) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, target);
	REQ_FLOAT_ARG(1, time);
	REQ_FLOAT_ARG(2, timeConstant);

	_impl->setTargetAtTime(target, time, timeConstant);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioParam, setValueCurveAtTime) {
	THIS_CHECK;
	REQ_OBJ_ARG(0, values);
	REQ_FLOAT_ARG(1, time);
	REQ_FLOAT_ARG(2, duration);

	std::vector<float> curve;
	// TODO: read array

	_impl->setValueCurveAtTime(curve, time, duration);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioParam, cancelScheduledValues) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, startTime);

	_impl->cancelScheduledValues(startTime);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioParam, cancelAndHoldAtTime) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, startTime);

	// TODO: implement
	// _impl->cancelAndHoldAtTime(startTime);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(AudioParam, value) {
	THIS_CHECK;
	Napi::Object context = _context.Value();
	AudioContext *audioContext = AudioContext::unwrap(context);

	lab::ContextRenderLock renderLock(audioContext->getCtx().get(), "AudioParam::valueGetter");

	RET_NUM(_impl->value());
}

JS_IMPLEMENT_SETTER(AudioParam, value) {
	THIS_CHECK;
	SETTER_FLOAT_ARG;
	_impl->setValue(v);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(AudioParam, defaultValue) {
	THIS_CHECK;
	RET_NUM(_impl->defaultValue());
}


JS_IMPLEMENT_GETTER(AudioParam, minValue) {
	THIS_CHECK;
	RET_NUM(_impl->minValue());
}


JS_IMPLEMENT_GETTER(AudioParam, maxValue) {
	THIS_CHECK;
	RET_NUM(_impl->maxValue());
}


JS_IMPLEMENT_METHOD(AudioParam, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
