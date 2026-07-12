#pragma once

#include "common.hpp"


class AudioNode : public CommonNode {
	DECLARE_ES5_CLASS(AudioNode, AudioNode);

  public:
	static void init(Napi::Env env, Napi::Object exports);
	static bool isAudioNode(Napi::Object obj);

	~AudioNode();
	explicit AudioNode(const Napi::CallbackInfo &info);

	void _destroy();

  private:
	std::string _channelCountMode;
	std::string _channelInterpretation;

	JS_DECLARE_METHOD(AudioNode, destroy);
	JS_DECLARE_METHOD(AudioNode, diagnose);

	JS_DECLARE_METHOD(AudioNode, connect);
	JS_DECLARE_METHOD(AudioNode, disconnect);

	JS_DECLARE_GETTER(AudioNode, context);

	JS_DECLARE_GETTER(AudioNode, numberOfInputs);

	JS_DECLARE_GETTER(AudioNode, numberOfOutputs);

	JS_DECLARE_GETTER(AudioNode, channelCount);
	JS_DECLARE_SETTER(AudioNode, channelCount);

	JS_DECLARE_GETTER(AudioNode, channelCountMode);
	JS_DECLARE_SETTER(AudioNode, channelCountMode);

	JS_DECLARE_GETTER(AudioNode, channelInterpretation);
	JS_DECLARE_SETTER(AudioNode, channelInterpretation);
};
