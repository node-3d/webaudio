#pragma once

#include "common.hpp"
#include "audio-node.hpp"


class ChannelSplitterNode : public CommonNode {
	DECLARE_ES5_CLASS(ChannelSplitterNode, ChannelSplitterNode);

  public:
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);

	explicit ChannelSplitterNode(const Napi::CallbackInfo &info);
	~ChannelSplitterNode();

	void _destroy();

  private:
	JS_DECLARE_METHOD(ChannelSplitterNode, destroy);
};
