#pragma once

#include "common.hpp"


class AudioListener : public CommonListener {
	DECLARE_ES5_CLASS(AudioListener, AudioListener);

  public:
	static void init(Napi::Env env, Napi::Object exports);

	explicit AudioListener(const Napi::CallbackInfo &info);
	~AudioListener();

	void _destroy();

  private:
	Napi::ObjectReference _positionX;
	Napi::ObjectReference _positionY;
	Napi::ObjectReference _positionZ;
	Napi::ObjectReference _forwardX;
	Napi::ObjectReference _forwardY;
	Napi::ObjectReference _forwardZ;
	Napi::ObjectReference _upX;
	Napi::ObjectReference _upY;
	Napi::ObjectReference _upZ;

	JS_DECLARE_METHOD(AudioListener, destroy);
	JS_DECLARE_METHOD(AudioListener, setPosition);
	JS_DECLARE_METHOD(AudioListener, setOrientation);

	JS_DECLARE_GETTER(AudioListener, positionX);
	JS_DECLARE_GETTER(AudioListener, positionY);
	JS_DECLARE_GETTER(AudioListener, positionZ);
	JS_DECLARE_GETTER(AudioListener, forwardX);
	JS_DECLARE_GETTER(AudioListener, forwardY);
	JS_DECLARE_GETTER(AudioListener, forwardZ);
	JS_DECLARE_GETTER(AudioListener, upX);
	JS_DECLARE_GETTER(AudioListener, upY);
	JS_DECLARE_GETTER(AudioListener, upZ);
};
