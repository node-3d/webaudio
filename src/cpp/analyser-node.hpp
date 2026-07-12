#pragma once

#include "common.hpp"
#include "audio-node.hpp"


class AnalyserNode : public CommonNode {
	DECLARE_ES5_CLASS(AnalyserNode, AnalyserNode);

  public:
	static void init(Napi::Env env, Napi::Object exports);

	explicit AnalyserNode(const Napi::CallbackInfo &info);
	~AnalyserNode();

	void _destroy();

  private:
	uint32_t _fftSize;
	double _minDecibels;
	double _maxDecibels;
	double _smoothingTimeConstant;

	JS_DECLARE_METHOD(AnalyserNode, destroy);
	JS_DECLARE_METHOD(AnalyserNode, getFloatFrequencyData);
	JS_DECLARE_METHOD(AnalyserNode, getByteFrequencyData);
	JS_DECLARE_METHOD(AnalyserNode, getFloatTimeDomainData);
	JS_DECLARE_METHOD(AnalyserNode, getByteTimeDomainData);

	JS_DECLARE_GETTER(AnalyserNode, frequencyBinCount);

	JS_DECLARE_GETTER(AnalyserNode, fftSize);
	JS_DECLARE_SETTER(AnalyserNode, fftSize);

	JS_DECLARE_GETTER(AnalyserNode, minDecibels);
	JS_DECLARE_SETTER(AnalyserNode, minDecibels);

	JS_DECLARE_GETTER(AnalyserNode, maxDecibels);
	JS_DECLARE_SETTER(AnalyserNode, maxDecibels);

	JS_DECLARE_GETTER(AnalyserNode, smoothingTimeConstant);
	JS_DECLARE_SETTER(AnalyserNode, smoothingTimeConstant);
};
