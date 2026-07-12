#include "convolver-node.hpp"
#include "audio-context.hpp"
#include "audio-buffer.hpp"


IMPLEMENT_ES5_CLASS(ConvolverNode);

void ConvolverNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(normalize);
	JS_ASSIGN_SETTER(buffer);
	JS_ASSIGN_METHOD(destroy);

	exports.Set("ConvolverNode", ctor);
}


ConvolverNode::ConvolverNode(const Napi::CallbackInfo &info) : CommonNode(info.This(), "ConvolverNode") {
	NAPI_ENV;
	Napi::Object context = info[0].As<Napi::Object>();

	AudioContext *contextUnwrap = AudioContext::unwrap(context);
	lab::AudioContext *contextLab = contextUnwrap->getCtx().get();
	reset(context, std::make_shared<lab::ConvolverNode>(*contextLab));

	lab::ConvolverNode *node = static_cast<lab::ConvolverNode *>(_impl.get());

	Napi::Value argv[] = { context, JS_EXT(&_impl) };
	super(info, 2, argv);
}


ConvolverNode::~ConvolverNode() {
	_destroy();
}


void ConvolverNode::_destroy() {
	DES_CHECK;
	CommonNode::_destroy();
}


JS_IMPLEMENT_GETTER(ConvolverNode, buffer) {
	THIS_CHECK;
	RET_VALUE(_buffer.Value());
}


JS_IMPLEMENT_SETTER(ConvolverNode, buffer) {
	THIS_CHECK;
	SETTER_OBJ_ARG;
	if (!v && v == _buffer.Value()) {
		RET_UNDEFINED;
	}
	_buffer.Reset(v, 1);

	Napi::Object context = _context.Value();
	AudioContext *audioContext = AudioContext::unwrap(context);

	lab::AudioContext *ctx = audioContext->getCtx().get();

	AudioBuffer *audioBuffer = AudioBuffer::unwrap(v);
	BusPtr bus = audioBuffer->getBus();

	lab::ConvolverNode *node = static_cast<lab::ConvolverNode *>(_impl.get());
	node->setImpulse(bus);

	emit("buffer", 1, &value);

	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(ConvolverNode, normalize) {
	THIS_CHECK;
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode *>(_impl.get());

	RET_BOOL(node->normalize());
}

JS_IMPLEMENT_SETTER(ConvolverNode, normalize) {
	THIS_CHECK;
	SETTER_BOOL_ARG;
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode *>(_impl.get());

	node->setNormalize(v);

	emit("normalize", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(ConvolverNode, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
