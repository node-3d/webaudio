
#include "offline-audio-context.hpp"


OfflineAudioContext::OfflineAudioContext() : BaseAudioContext() {
	_isDestroyed = false;
}


OfflineAudioContext::~OfflineAudioContext() {
	_destroy();
}


void OfflineAudioContext::_destroy() {
	DES_CHECK;

	_isDestroyed = true;

	BaseAudioContext::_destroy();
}


// ------ Methods and props


JS_IMPLEMENT_METHOD(OfflineAudioContext, startRendering) {
	THIS_CHECK;

	// TODO: do something?
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(OfflineAudioContext, suspend) {
	THIS_CHECK;

	REQ_DOUBLE_ARG(0, suspendTime);

	// TODO: do something?
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(OfflineAudioContext, oncomplete) {
	THIS_CHECK;

	RET_VALUE(JS_FUN(_oncomplete));
}

JS_IMPLEMENT_SETTER(OfflineAudioContext, oncomplete) {
	THIS_SETTER_CHECK;
	SETTER_FUN_ARG;

	if (Nan::New(_oncomplete) == v) {
		return;
	}
	_oncomplete.Reset(v, 1);

	// TODO: may be additional actions on change?

	emit("oncomplete", 1, &value);
}


JS_IMPLEMENT_GETTER(OfflineAudioContext, length) {
	THIS_CHECK;

	RET_NUM(_length);
}


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(OfflineAudioContext);


void OfflineAudioContext::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(oncomplete);
	JS_ASSIGN_METHOD(suspend);
	JS_ASSIGN_METHOD(startRendering);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(length);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("OfflineAudioContext", ctor);
}


bool OfflineAudioContext::isOfflineAudioContext(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object OfflineAudioContext::getNew() {
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0 /*argc*/, nullptr /*argv*/).ToLocalChecked();
}


OfflineAudioContext::OfflineAudioContext(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<OfflineAudioContext>(info) {
	OfflineAudioContext *offlineAudioContext = new OfflineAudioContext();
}


JS_IMPLEMENT_METHOD(OfflineAudioContext, destroy) {
	THIS_CHECK;

	emit("destroy");

	_destroy();
}


JS_IMPLEMENT_GETTER(OfflineAudioContext, isDestroyed) {
	NAPI_ENV;

	RET_BOOL(_isDestroyed);
}
