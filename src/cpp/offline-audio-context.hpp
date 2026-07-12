#pragma once

#include "common.hpp"


class OfflineAudioContext : public BaseAudioContext {
  public:
	~OfflineAudioContext();
	explicit OfflineAudioContext(const Napi::CallbackInfo &info);

	static void init(Napi::Env env, Napi::Object exports);

	static bool isOfflineAudioContext(Napi::Object obj);

	// Destroy an instance from C++ land
	void _destroy();


  protected:
	OfflineAudioContext();

	static Napi::FunctionReference _constructor;

	bool _isDestroyed;

	V8_STORE_FUNC _oncomplete;
	uint32_t _length;


  private:
	JS_DECLARE_METHOD(OfflineAudioContext, destroy);
	JS_DECLARE_GETTER(OfflineAudioContext, isDestroyed);

	JS_DECLARE_METHOD(OfflineAudioContext, startRendering);
	JS_DECLARE_METHOD(OfflineAudioContext, suspend);

	JS_DECLARE_GETTER(OfflineAudioContext, oncomplete);
	JS_DECLARE_SETTER(OfflineAudioContext, oncomplete);

	JS_DECLARE_GETTER(OfflineAudioContext, length);
};
