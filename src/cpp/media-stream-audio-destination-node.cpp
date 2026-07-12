
#include "media-stream-audio-destination-node.hpp"


MediaStreamAudioDestinationNode::MediaStreamAudioDestinationNode() : AudioNode() {
	_isDestroyed = false;
}


MediaStreamAudioDestinationNode::~MediaStreamAudioDestinationNode() {
	_destroy();
}


void MediaStreamAudioDestinationNode::_destroy() {
	DES_CHECK;

	_isDestroyed = true;

	AudioNode::_destroy();
}


// ------ Methods and props


JS_IMPLEMENT_GETTER(MediaStreamAudioDestinationNode, stream) {
	THIS_CHECK;

	RET_VALUE(_stream.Value());
}


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(MediaStreamAudioDestinationNode);


void MediaStreamAudioDestinationNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(stream);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("MediaStreamAudioDestinationNode", ctor);
}


bool MediaStreamAudioDestinationNode::isMediaStreamAudioDestinationNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object MediaStreamAudioDestinationNode::getNew() {
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0 /*argc*/, nullptr /*argv*/).ToLocalChecked();
}


MediaStreamAudioDestinationNode::MediaStreamAudioDestinationNode(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<MediaStreamAudioDestinationNode>(info) {
	MediaStreamAudioDestinationNode *mediaStreamAudioDestinationNode = new MediaStreamAudioDestinationNode();
}


JS_IMPLEMENT_METHOD(MediaStreamAudioDestinationNode, destroy) {
	THIS_CHECK;

	emit("destroy");

	_destroy();
}


JS_IMPLEMENT_GETTER(MediaStreamAudioDestinationNode, isDestroyed) {
	NAPI_ENV;

	RET_BOOL(_isDestroyed);
}
