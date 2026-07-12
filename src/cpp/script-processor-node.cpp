
#include "script-processor-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

ScriptProcessorNode::ScriptProcessorNode() : AudioNode() {
	_isDestroyed = false;
}


ScriptProcessorNode::~ScriptProcessorNode() {
	_destroy();
}


void ScriptProcessorNode::_destroy() {
	DES_CHECK;

	_isDestroyed = true;

	AudioNode::_destroy();
}


// ------ Methods and props


JS_IMPLEMENT_GETTER(ScriptProcessorNode, onaudioprocess) {
	THIS_CHECK;

	RET_VALUE(JS_FUN(_onaudioprocess));
}

JS_IMPLEMENT_SETTER(ScriptProcessorNode, onaudioprocess) {
	THIS_SETTER_CHECK;
	SETTER_FUN_ARG;

	if (Nan::New(_onaudioprocess) == v) {
		return;
	}
	_onaudioprocess.Reset(v, 1);

	// TODO: may be additional actions on change?

	emit("onaudioprocess", 1, &value);
}


JS_IMPLEMENT_GETTER(ScriptProcessorNode, bufferSize) {
	THIS_CHECK;

	RET_NUM(_bufferSize);
}


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(ScriptProcessorNode);


void ScriptProcessorNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(onaudioprocess);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(bufferSize);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("ScriptProcessorNode", ctor);
}


bool ScriptProcessorNode::isScriptProcessorNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object ScriptProcessorNode::getNew() {
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0 /*argc*/, nullptr /*argv*/).ToLocalChecked();
}


ScriptProcessorNode::ScriptProcessorNode(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<ScriptProcessorNode>(info) {
	ScriptProcessorNode *scriptProcessorNode = new ScriptProcessorNode();
}


JS_IMPLEMENT_METHOD(ScriptProcessorNode, destroy) {
	THIS_CHECK;

	emit("destroy");

	_destroy();
}


JS_IMPLEMENT_GETTER(ScriptProcessorNode, isDestroyed) {
	NAPI_ENV;

	RET_BOOL(_isDestroyed);
}
