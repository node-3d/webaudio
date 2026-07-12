#include "wave-shaper-node.hpp"


IMPLEMENT_ES5_CLASS(WaveShaperNode);

void WaveShaperNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(oversample);
	JS_ASSIGN_SETTER(curve);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(isDestroyed);

	exports.Set("WaveShaperNode", ctor);
}


WaveShaperNode::WaveShaperNode(const Napi::CallbackInfo &info) : AudioNode() {
	_isDestroyed = false;
}


// ------ Methods and props


JS_IMPLEMENT_GETTER(WaveShaperNode, curve) {
	THIS_CHECK;

	RET_VALUE(_curve.Value());
}

JS_IMPLEMENT_SETTER(WaveShaperNode, curve) {
	THIS_SETTER_CHECK;
	SETTER_OBJ_ARG;

	if (Nan::New(_curve) == v) {
		return;
	}
	_curve.Reset(v, 1);

	// TODO: may be additional actions on change?

	emit("curve", 1, &value);
}


JS_IMPLEMENT_GETTER(WaveShaperNode, oversample) {
	THIS_CHECK;

	RET_STR(_oversample);
}

JS_IMPLEMENT_SETTER(WaveShaperNode, oversample) {
	THIS_SETTER_CHECK;
	SETTER_STR_ARG;

	CACHE_CAS(_oversample, v)

	// TODO: may be additional actions on change?

	emit("oversample", 1, &value);
}
