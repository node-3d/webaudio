
#include "iir-filter-node.hpp"


IIRFilterNode::IIRFilterNode() : AudioNode() {
	_isDestroyed = false;
}


IIRFilterNode::~IIRFilterNode() {
	_destroy();
}


void IIRFilterNode::_destroy() {
	DES_CHECK;

	_isDestroyed = true;

	AudioNode::_destroy();
}


// ------ Methods and props


JS_IMPLEMENT_METHOD(IIRFilterNode, getFrequencyResponse) {
	THIS_CHECK;

	REQ_OBJ_ARG(0, frequencyHz);
	REQ_OBJ_ARG(1, magResponse);
	REQ_OBJ_ARG(2, phaseResponse);

	// TODO: do something?
	RET_UNDEFINED;
}


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(IIRFilterNode);


void IIRFilterNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(getFrequencyResponse);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("IIRFilterNode", ctor);
}


bool IIRFilterNode::isIIRFilterNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object IIRFilterNode::getNew() {
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0 /*argc*/, nullptr /*argv*/).ToLocalChecked();
}


IIRFilterNode::IIRFilterNode(const Napi::CallbackInfo &info) : Napi::ObjectWrap<IIRFilterNode>(info) {
	IIRFilterNode *iIRFilterNode = new IIRFilterNode();
}


JS_IMPLEMENT_METHOD(IIRFilterNode, destroy) {
	THIS_CHECK;

	emit("destroy");

	_destroy();
}


JS_IMPLEMENT_GETTER(IIRFilterNode, isDestroyed) {
	NAPI_ENV;

	RET_BOOL(_isDestroyed);
}
