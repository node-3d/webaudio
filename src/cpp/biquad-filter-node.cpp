#include "biquad-filter-node.hpp"
#include "audio-param.hpp"
#include "audio-context.hpp"


IMPLEMENT_ES5_CLASS(BiquadFilterNode);

void BiquadFilterNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(type);
	JS_ASSIGN_METHOD(getFrequencyResponse);
	JS_ASSIGN_GETTER(gain);
	JS_ASSIGN_GETTER(Q);
	JS_ASSIGN_GETTER(detune);
	JS_ASSIGN_GETTER(frequency);
	JS_ASSIGN_METHOD(destroy);

	exports.Set("BiquadFilterNode", ctor);
}


BiquadFilterNode::BiquadFilterNode(const Napi::CallbackInfo &info)
    : CommonNode(info.This(), "BiquadFilterNode") {
	NAPI_ENV;
	Napi::Object context = info[0].As<Napi::Object>();
	Napi::Function paramCtor = info[1].As<Napi::Function>();
	Napi::Object opts = info[2].As<Napi::Object>();

	AudioContext *contextUnwrap = AudioContext::unwrap(context);
	lab::AudioContext *contextLab = contextUnwrap->getCtx().get();
	reset(context, std::make_shared<lab::BiquadFilterNode>(*contextLab));

	lab::BiquadFilterNode *node = static_cast<lab::BiquadFilterNode *>(_impl.get());

	napi_value argv[2];
	argv[0] = context;

	ParamPtr frequencyParam = node->frequency();
	argv[1] = JS_EXT(&frequencyParam);
	_frequency.Reset(paramCtor.New(2, argv), 1);

	ParamPtr detuneParam = node->detune();
	argv[1] = JS_EXT(&detuneParam);
	_detune.Reset(paramCtor.New(2, argv), 1);

	ParamPtr qParam = node->q();
	argv[1] = JS_EXT(&qParam);
	_Q.Reset(paramCtor.New(2, argv), 1);

	ParamPtr gainParam = node->gain();
	argv[1] = JS_EXT(&gainParam);
	_gain.Reset(paramCtor.New(2, argv), 1);

	argv[1] = JS_EXT(&_impl);
	super(info, 2, argv);
}


BiquadFilterNode::~BiquadFilterNode() {
	_destroy();
}


void BiquadFilterNode::_destroy() {
	DES_CHECK;
	_frequency.Reset();
	_detune.Reset();
	_Q.Reset();
	_gain.Reset();

	CommonNode::_destroy();
}


// ------ Methods and props


JS_IMPLEMENT_METHOD(BiquadFilterNode, getFrequencyResponse) {
	THIS_CHECK;
	REQ_OBJ_ARG(0, frequencyHz);
	REQ_OBJ_ARG(1, magResponse);
	REQ_OBJ_ARG(2, phaseResponse);

	// TODO: do something?
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(BiquadFilterNode, type) {
	THIS_CHECK;
	RET_STR(_type);
}

JS_IMPLEMENT_SETTER(BiquadFilterNode, type) {
	THIS_CHECK;
	SETTER_STR_ARG;
	CACHE_CAS(_type, v);

	// TODO: may be additional actions on change?

	emit("type", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(BiquadFilterNode, frequency) {
	THIS_CHECK;
	RET_VALUE(_frequency.Value());
}


JS_IMPLEMENT_GETTER(BiquadFilterNode, detune) {
	THIS_CHECK;
	RET_VALUE(_detune.Value());
}


JS_IMPLEMENT_GETTER(BiquadFilterNode, Q) {
	THIS_CHECK;
	RET_VALUE(_Q.Value());
}


JS_IMPLEMENT_GETTER(BiquadFilterNode, gain) {
	THIS_CHECK;
	RET_VALUE(_gain.Value());
}


JS_IMPLEMENT_METHOD(BiquadFilterNode, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
