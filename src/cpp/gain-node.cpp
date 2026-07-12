#include "gain-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


IMPLEMENT_ES5_CLASS(GainNode);

void GainNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_GETTER(gain);
	JS_ASSIGN_METHOD(destroy);

	exports.Set("GainNode", ctor);
}


GainNode::GainNode(const Napi::CallbackInfo &info) : CommonNode(info.This(), "GainNode") {
	NAPI_ENV;
	Napi::Object context = info[0].As<Napi::Object>();
	Napi::Function paramCtor = info[1].As<Napi::Function>();

	AudioContext *contextUnwrap = AudioContext::unwrap(context);
	lab::AudioContext *contextLab = contextUnwrap->getCtx().get();
	reset(context, std::make_shared<lab::GainNode>(*contextLab));

	lab::GainNode *node = static_cast<lab::GainNode *>(_impl.get());

	napi_value argv[2];
	argv[0] = context;

	ParamPtr gainParam = node->gain();
	argv[1] = JS_EXT(&gainParam);
	_gain.Reset(paramCtor.New(2, argv), 1);

	argv[1] = JS_EXT(&_impl);
	super(info, 2, argv);
}


GainNode::~GainNode() {
	_destroy();
}


void GainNode::_destroy() {
	DES_CHECK;
	_gain.Reset();

	CommonNode::_destroy();
}


JS_IMPLEMENT_GETTER(GainNode, gain) {
	THIS_CHECK;
	RET_VALUE(_gain.Value());
}


JS_IMPLEMENT_METHOD(GainNode, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
