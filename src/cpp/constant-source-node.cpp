
#include "constant-source-node.hpp"


ConstantSourceNode::ConstantSourceNode() : AudioScheduledSourceNode() {
	_isDestroyed = false;
}


ConstantSourceNode::~ConstantSourceNode() {
	_destroy();
}


void ConstantSourceNode::_destroy() {
	DES_CHECK;

	_isDestroyed = true;

	AudioScheduledSourceNode::_destroy();
}


// ------ Methods and props


JS_IMPLEMENT_GETTER(ConstantSourceNode, offset) {
	THIS_CHECK;

	RET_VALUE(_offset.Value());
}


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(ConstantSourceNode);


void ConstantSourceNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(offset);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("ConstantSourceNode", ctor);
}


bool ConstantSourceNode::isConstantSourceNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object ConstantSourceNode::getNew() {
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0 /*argc*/, nullptr /*argv*/).ToLocalChecked();
}


ConstantSourceNode::ConstantSourceNode(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<ConstantSourceNode>(info) {
	ConstantSourceNode *constantSourceNode = new ConstantSourceNode();
}


JS_IMPLEMENT_METHOD(ConstantSourceNode, destroy) {
	THIS_CHECK;

	emit("destroy");

	_destroy();
}


JS_IMPLEMENT_GETTER(ConstantSourceNode, isDestroyed) {
	NAPI_ENV;

	RET_BOOL(_isDestroyed);
}
