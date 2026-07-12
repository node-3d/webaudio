
#include <LabSound/LabSound.h>

#include "channel-splitter-node.hpp"

#include "common.hpp"


IMPLEMENT_ES5_CLASS(ChannelSplitterNode);

void ChannelSplitterNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("ChannelSplitterNode", ctor);
}


ChannelSplitterNode::ChannelSplitterNode(const Napi::CallbackInfo &info)
    : CommonNode(info.This(), "ChannelSplitterNode") {
	NAPI_ENV;

	REQ_OBJ_ARG(0, context);

	reset(context, std::make_shared<lab::ChannelSplitterNode>());

	Napi::Value argv[] = { static_cast<Napi::Value>(context),
		                   static_cast<Napi::Value>(JS_NUM(reinterpret_cast<size_t>(&_impl))) };
	super(info, 2, argv);
}


ChannelSplitterNode::~ChannelSplitterNode() {
	_destroy();
}


void ChannelSplitterNode::_destroy() {
	DES_CHECK;

	_isDestroyed = true;

	CommonNode::_destroy();
}


JS_IMPLEMENT_METHOD(ChannelSplitterNode, destroy) {
	THIS_CHECK;

	emit("destroy");

	_destroy();
	RET_UNDEFINED;
}
