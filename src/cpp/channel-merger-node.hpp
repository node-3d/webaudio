#pragma once

#include "common.hpp"
#include "audio-node.hpp"


class ChannelMergerNode : public CommonNode {
	DECLARE_ES5_CLASS(ChannelMergerNode, ChannelMergerNode);

  public:
	~ChannelMergerNode();
	explicit ChannelMergerNode(const Napi::CallbackInfo &info);

	static void init(Napi::Env env, Napi::Object exports);
};
