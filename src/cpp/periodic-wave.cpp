
#include "periodic-wave.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

PeriodicWave::PeriodicWave() {
	_isDestroyed = false;
}


PeriodicWave::~PeriodicWave() {
	_destroy();
}


void PeriodicWave::_destroy() {
	DES_CHECK;

	_isDestroyed = true;
}


// ------ Methods and props


// ------ System methods and props for Napi::ObjectWrap

IMPLEMENT_ES5_CLASS(PeriodicWave);


void PeriodicWave::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("PeriodicWave", ctor);
}


bool PeriodicWave::isPeriodicWave(Napi::Object obj) {
	return obj.InstanceOf(_ctorEs5.Value());
}


Napi::Object PeriodicWave::getNew() {
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0 /*argc*/, nullptr /*argv*/).ToLocalChecked();
}


PeriodicWave::PeriodicWave(const Napi::CallbackInfo &info) : Napi::ObjectWrap<PeriodicWave>(info) {
	PeriodicWave *periodicWave = new PeriodicWave();
}


JS_IMPLEMENT_METHOD(PeriodicWave, destroy) {
	THIS_CHECK;

	_destroy();
}


JS_IMPLEMENT_GETTER(PeriodicWave, isDestroyed) {
	NAPI_ENV;

	RET_BOOL(_isDestroyed);
}
