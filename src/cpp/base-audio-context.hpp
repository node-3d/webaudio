#pragma once

#include "common.hpp"


class BaseAudioContext : public CommonCtx {
	DECLARE_ES5_CLASS(BaseAudioContext, BaseAudioContext);

  public:
	static void init(Napi::Env env, Napi::Object exports);

	explicit BaseAudioContext(const Napi::CallbackInfo &info);
	~BaseAudioContext();

	void _destroy();

  private:
	Napi::ObjectReference _destination;
	Napi::ObjectReference _listener;
	std::string _state;

	JS_DECLARE_METHOD(BaseAudioContext, destroy);
	JS_DECLARE_METHOD(BaseAudioContext, _initListener);
	JS_DECLARE_METHOD(BaseAudioContext, update);
	JS_DECLARE_METHOD(BaseAudioContext, resume);
	JS_DECLARE_METHOD(BaseAudioContext, decodeAudioData);

	JS_DECLARE_GETTER(BaseAudioContext, destination);
	JS_DECLARE_GETTER(BaseAudioContext, currentTime);
	JS_DECLARE_GETTER(BaseAudioContext, sampleRate);
	JS_DECLARE_GETTER(BaseAudioContext, listener);
	JS_DECLARE_GETTER(BaseAudioContext, state);
};
