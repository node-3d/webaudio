#pragma once

#include "common.hpp"


class AudioParam : public CommonParam {
	DECLARE_ES5_CLASS(AudioParam, AudioParam);

  public:
	static void init(Napi::Env env, Napi::Object exports);
	static bool isAudioParam(Napi::Object obj);

	explicit AudioParam(const Napi::CallbackInfo &info);
	~AudioParam();

	void _destroy();

  private:
	JS_DECLARE_METHOD(AudioParam, destroy);

	// JS_METHOD(connect);
	// JS_METHOD(disconnect);

	// JS_GETTER(context);

	JS_DECLARE_METHOD(AudioParam, setValueAtTime);
	JS_DECLARE_METHOD(AudioParam, linearRampToValueAtTime);
	JS_DECLARE_METHOD(AudioParam, exponentialRampToValueAtTime);
	JS_DECLARE_METHOD(AudioParam, setTargetAtTime);
	JS_DECLARE_METHOD(AudioParam, setValueCurveAtTime);
	JS_DECLARE_METHOD(AudioParam, cancelScheduledValues);
	JS_DECLARE_METHOD(AudioParam, cancelAndHoldAtTime);

	JS_DECLARE_GETTER(AudioParam, value);
	JS_DECLARE_SETTER(AudioParam, value);
	JS_DECLARE_GETTER(AudioParam, defaultValue);
	JS_DECLARE_GETTER(AudioParam, minValue);
	JS_DECLARE_GETTER(AudioParam, maxValue);
};
