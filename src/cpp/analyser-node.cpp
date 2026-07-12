#include "analyser-node.hpp"
#include "audio-context.hpp"


IMPLEMENT_ES5_CLASS(AnalyserNode);

void AnalyserNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(smoothingTimeConstant);
	JS_ASSIGN_SETTER(maxDecibels);
	JS_ASSIGN_SETTER(minDecibels);
	JS_ASSIGN_SETTER(fftSize);
	JS_ASSIGN_METHOD(getByteTimeDomainData);
	JS_ASSIGN_METHOD(getFloatTimeDomainData);
	JS_ASSIGN_METHOD(getByteFrequencyData);
	JS_ASSIGN_METHOD(getFloatFrequencyData);
	JS_ASSIGN_GETTER(frequencyBinCount);
	JS_ASSIGN_METHOD(destroy);

	exports.Set("AnalyserNode", ctor);
}


AnalyserNode::AnalyserNode(const Napi::CallbackInfo &info) : CommonNode(info.This(), "AnalyserNode") {
	NAPI_ENV;
	Napi::Object context = info[0].As<Napi::Object>();
	Napi::Object opts = info[2].As<Napi::Object>();

	AudioContext *contextUnwrap = AudioContext::unwrap(context);
	lab::AudioContext *contextLab = contextUnwrap->getCtx().get();
	reset(context, std::make_shared<lab::AnalyserNode>(*contextLab));

	lab::AnalyserNode *node = static_cast<lab::AnalyserNode *>(_impl.get());

	// TODO OPTS

	Napi::Value argv[] = { context, JS_EXT(&_impl) };
	super(info, 2, argv);
}


AnalyserNode::~AnalyserNode() {
	_destroy();
}


void AnalyserNode::_destroy() {
	DES_CHECK;
	CommonNode::_destroy();
}


JS_IMPLEMENT_METHOD(AnalyserNode, getFloatFrequencyData) {
	THIS_CHECK;
	REQ_TYPED_ARRAY_ARG(0, array);

	lab::AnalyserNode *node = static_cast<lab::AnalyserNode *>(_impl.get());
	std::vector<float> cppArray;
	node->getFloatFrequencyData(cppArray);

	for (int i = 0; i < cppArray.size(); i++) {
		array.Set(i, cppArray[i]);
	}

	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AnalyserNode, getByteFrequencyData) {
	THIS_CHECK;
	REQ_TYPED_ARRAY_ARG(0, array);

	lab::AnalyserNode *node = static_cast<lab::AnalyserNode *>(_impl.get());
	std::vector<uint8_t> cppArray;
	node->getByteFrequencyData(cppArray);

	for (int i = 0; i < cppArray.size(); i++) {
		array.Set(i, cppArray[i]);
	}

	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AnalyserNode, getFloatTimeDomainData) {
	THIS_CHECK;
	REQ_TYPED_ARRAY_ARG(0, array);

	lab::AnalyserNode *node = static_cast<lab::AnalyserNode *>(_impl.get());
	std::vector<float> cppArray;
	node->getFloatTimeDomainData(cppArray);

	for (int i = 0; i < cppArray.size(); i++) {
		array.Set(i, cppArray[i]);
	}

	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AnalyserNode, getByteTimeDomainData) {
	THIS_CHECK;
	REQ_TYPED_ARRAY_ARG(0, array);

	lab::AnalyserNode *node = static_cast<lab::AnalyserNode *>(_impl.get());
	std::vector<uint8_t> cppArray;
	node->getByteTimeDomainData(cppArray);

	for (int i = 0; i < cppArray.size(); i++) {
		array.Set(i, cppArray[i]);
	}

	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(AnalyserNode, frequencyBinCount) {
	THIS_CHECK;
	RET_NUM(_fftSize / 2);
}


JS_IMPLEMENT_GETTER(AnalyserNode, fftSize) {
	THIS_CHECK;
	RET_NUM(_fftSize);
}

JS_IMPLEMENT_SETTER(AnalyserNode, fftSize) {
	THIS_CHECK;
	SETTER_UINT32_ARG;
	CACHE_CAS(_fftSize, v);

	lab::AnalyserNode *node = static_cast<lab::AnalyserNode *>(_impl.get());

	Napi::Object context = _context.Value();
	AudioContext *audioContext = AudioContext::unwrap(context);
	lab::ContextRenderLock renderLock(audioContext->getCtx().get(), "AnalyserNode::fftSize");

	node->setFftSize(renderLock, v);

	emit("fftSize", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(AnalyserNode, minDecibels) {
	THIS_CHECK;
	RET_NUM(_minDecibels);
}

JS_IMPLEMENT_SETTER(AnalyserNode, minDecibels) {
	THIS_CHECK;
	SETTER_DOUBLE_ARG;
	CACHE_CAS(_minDecibels, v);

	lab::AnalyserNode *node = static_cast<lab::AnalyserNode *>(_impl.get());
	node->setMinDecibels(v);

	emit("minDecibels", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(AnalyserNode, maxDecibels) {
	THIS_CHECK;
	RET_NUM(_maxDecibels);
}

JS_IMPLEMENT_SETTER(AnalyserNode, maxDecibels) {
	THIS_CHECK;
	SETTER_DOUBLE_ARG;
	CACHE_CAS(_maxDecibels, v);

	lab::AnalyserNode *node = static_cast<lab::AnalyserNode *>(_impl.get());
	node->setMaxDecibels(v);

	emit("maxDecibels", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(AnalyserNode, smoothingTimeConstant) {
	THIS_CHECK;
	RET_NUM(_smoothingTimeConstant);
}


JS_IMPLEMENT_SETTER(AnalyserNode, smoothingTimeConstant) {
	THIS_CHECK;
	SETTER_DOUBLE_ARG;
	CACHE_CAS(_smoothingTimeConstant, v);

	lab::AnalyserNode *node = static_cast<lab::AnalyserNode *>(_impl.get());
	node->setSmoothingTimeConstant(v);

	emit("smoothingTimeConstant", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AnalyserNode, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
