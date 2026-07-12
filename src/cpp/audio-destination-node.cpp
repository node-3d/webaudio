#include "audio-destination-node.hpp"


IMPLEMENT_ES5_CLASS(AudioDestinationNode);

void AudioDestinationNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_GETTER(maxChannelCount);
	JS_ASSIGN_METHOD(destroy);
	exports.Set("AudioDestinationNode", ctor);
}


AudioDestinationNode::AudioDestinationNode(const Napi::CallbackInfo &info)
    : CommonNode(info.This(), "AudioDestinationNode") {
	NAPI_ENV;
	Napi::Object context = info[0].As<Napi::Object>();
	Napi::External<void> extNode = info[1].As<Napi::External<void>>();
	NodePtr *node = reinterpret_cast<NodePtr *>(extNode.Data());

	reset(context, *node);

	Napi::Value argv[] = { context, extNode };
	super(info, 2, argv);
}


AudioDestinationNode::~AudioDestinationNode() {
	_destroy();
}


void AudioDestinationNode::_destroy() {
	DES_CHECK;
	CommonNode::_destroy();
}


JS_IMPLEMENT_GETTER(AudioDestinationNode, maxChannelCount) {
	THIS_CHECK;
	RET_NUM(_maxChannelCount);
}


JS_IMPLEMENT_METHOD(AudioDestinationNode, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
