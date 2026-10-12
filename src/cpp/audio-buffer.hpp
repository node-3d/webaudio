#pragma once

#include "common.hpp"


class AudioBuffer : public CommonBus {
	DECLARE_ES5_CLASS(AudioBuffer, AudioBuffer);

  public:
	static void init(Napi::Env env, Napi::Object exports);

	explicit AudioBuffer(const Napi::CallbackInfo &info);
	~AudioBuffer();

	void _destroy();
	BusPtr snapshotBus();

  private:
	std::vector<Napi::Reference<Napi::Float32Array>> _channelData;

	JS_DECLARE_METHOD(AudioBuffer, destroy);
	JS_DECLARE_METHOD(AudioBuffer, getChannelData);
	JS_DECLARE_METHOD(AudioBuffer, copyFromChannel);
	JS_DECLARE_METHOD(AudioBuffer, copyToChannel);

	JS_DECLARE_GETTER(AudioBuffer, length);
	JS_DECLARE_GETTER(AudioBuffer, duration);
	JS_DECLARE_GETTER(AudioBuffer, sampleRate);
	JS_DECLARE_GETTER(AudioBuffer, numberOfChannels);
};
