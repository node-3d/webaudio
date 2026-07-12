#include "delay-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


IMPLEMENT_ES5_CLASS(DelayNode);

void DelayNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_GETTER(delayTime);
	JS_ASSIGN_METHOD(destroy);

	exports.Set("DelayNode", ctor);
}


DelayNode::DelayNode(const Napi::CallbackInfo &info) : CommonNode(info.This(), "DelayNode") {
	NAPI_ENV;
	Napi::Object context = info[0].As<Napi::Object>();
	Napi::Function paramCtor = info[1].As<Napi::Function>();
	Napi::Object opts = info[2].As<Napi::Object>();
	double maxDelayTime = opts.Has("maxDelayTime") ? opts.Get("maxDelayTime").ToNumber().DoubleValue() : 1.0;

	AudioContext *contextUnwrap = AudioContext::unwrap(context);
	lab::AudioContext *contextLab = contextUnwrap->getCtx().get();
	reset(context, std::make_shared<lab::DelayNode>(*contextLab));

	lab::DelayNode *node = static_cast<lab::DelayNode *>(_impl.get());

	napi_value argv[2];
	argv[0] = context;

	SettingPtr delayTimeParam = node->delayTime();
	delayTimeParam->setFloat(0.f);

	argv[1] = JS_EXT(&delayTimeParam);
	_delayTime.Reset(paramCtor.New(2, argv), 1);

	argv[1] = JS_EXT(&_impl);
	super(info, 2, argv);
}


DelayNode::~DelayNode() {
	_destroy();
}


void DelayNode::_destroy() {
	DES_CHECK;
	_isDestroyed = true;
	CommonNode::_destroy();
}


JS_IMPLEMENT_GETTER(DelayNode, delayTime) {
	THIS_CHECK;
	if (_delayTime.IsEmpty()) {
		RET_UNDEFINED;
	}

	RET_VALUE(_delayTime.Value());
}


JS_IMPLEMENT_METHOD(DelayNode, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
