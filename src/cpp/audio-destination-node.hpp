#pragma once

#include "common.hpp"


class AudioDestinationNode : public CommonNode {
	DECLARE_ES5_CLASS(AudioDestinationNode, AudioDestinationNode);

  public:
	static void init(Napi::Env env, Napi::Object exports);

	explicit AudioDestinationNode(const Napi::CallbackInfo &info);
	~AudioDestinationNode();

	void _destroy();

  private:
	uint32_t _maxChannelCount;

	JS_DECLARE_METHOD(AudioDestinationNode, destroy);

	JS_DECLARE_GETTER(AudioDestinationNode, maxChannelCount);
};
