
#include "media-stream-audio-source-node.hpp"


MediaStreamAudioSourceNode::MediaStreamAudioSourceNode() : AudioNode() {
	_isDestroyed = false;
}


MediaStreamAudioSourceNode::~MediaStreamAudioSourceNode() {
	_destroy();
}


void MediaStreamAudioSourceNode::_destroy() {
	DES_CHECK;

	_isDestroyed = true;

	AudioNode::_destroy();
}


// ------ Methods and props


JS_IMPLEMENT_GETTER(MediaStreamAudioSourceNode, mediaStream) {
	THIS_CHECK;

	RET_VALUE(_mediaStream.Value());
}


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(MediaStreamAudioSourceNode);


void MediaStreamAudioSourceNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(mediaStream);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("MediaStreamAudioSourceNode", ctor);
}


bool MediaStreamAudioSourceNode::isMediaStreamAudioSourceNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object MediaStreamAudioSourceNode::getNew() {
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0 /*argc*/, nullptr /*argv*/).ToLocalChecked();
}


MediaStreamAudioSourceNode::MediaStreamAudioSourceNode(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<MediaStreamAudioSourceNode>(info) {
	MediaStreamAudioSourceNode *mediaStreamAudioSourceNode = new MediaStreamAudioSourceNode();
}


JS_IMPLEMENT_METHOD(MediaStreamAudioSourceNode, destroy) {
	THIS_CHECK;

	emit("destroy");

	_destroy();
}


JS_IMPLEMENT_GETTER(MediaStreamAudioSourceNode, isDestroyed) {
	NAPI_ENV;

	RET_BOOL(_isDestroyed);
}
