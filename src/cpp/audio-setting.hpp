#pragma once

#include "common.hpp"


class AudioSetting : public CommonSetting {
	DECLARE_ES5_CLASS(AudioSetting, AudioSetting);

  public:
	static void init(Napi::Env env, Napi::Object exports);
	static bool isAudioSetting(Napi::Object obj);

	explicit AudioSetting(const Napi::CallbackInfo &info);
	~AudioSetting();

	void _destroy();

  private:
	JS_DECLARE_METHOD(AudioSetting, destroy);

	// JS_METHOD(connect);
	// JS_METHOD(disconnect);

	// JS_GETTER(context);

	JS_DECLARE_METHOD(AudioSetting, setValueAtTime);
	JS_DECLARE_METHOD(AudioSetting, linearRampToValueAtTime);
	JS_DECLARE_METHOD(AudioSetting, exponentialRampToValueAtTime);
	JS_DECLARE_METHOD(AudioSetting, setTargetAtTime);
	JS_DECLARE_METHOD(AudioSetting, setValueCurveAtTime);
	JS_DECLARE_METHOD(AudioSetting, cancelScheduledValues);
	JS_DECLARE_METHOD(AudioSetting, cancelAndHoldAtTime);

	JS_DECLARE_GETTER(AudioSetting, value);
	JS_DECLARE_SETTER(AudioSetting, value);
	JS_DECLARE_GETTER(AudioSetting, defaultValue);
	JS_DECLARE_GETTER(AudioSetting, minValue);
	JS_DECLARE_GETTER(AudioSetting, maxValue);
};
