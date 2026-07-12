
#include "channel-merger-node.hpp"


ChannelMergerNode::ChannelMergerNode() : AudioNode() {
	_isDestroyed = false;
}


ChannelMergerNode::~ChannelMergerNode() {
	_destroy();
}


void ChannelMergerNode::_destroy() {
	DES_CHECK;

	_isDestroyed = true;

	AudioNode::_destroy();
}


// ------ Methods and props


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(ChannelMergerNode);


void ChannelMergerNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("ChannelMergerNode", ctor);
}


bool ChannelMergerNode::isChannelMergerNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object ChannelMergerNode::getNew() {
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0 /*argc*/, nullptr /*argv*/).ToLocalChecked();
}


ChannelMergerNode::ChannelMergerNode(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<ChannelMergerNode>(info) {
	ChannelMergerNode *channelMergerNode = new ChannelMergerNode();
}


JS_IMPLEMENT_METHOD(ChannelMergerNode, destroy) {
	THIS_CHECK;

	emit("destroy");

	_destroy();
}


JS_IMPLEMENT_GETTER(ChannelMergerNode, isDestroyed) {
	NAPI_ENV;

	RET_BOOL(_isDestroyed);
}
