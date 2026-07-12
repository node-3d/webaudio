#pragma once

#include "common.hpp"


class BiquadFilterNode : public CommonNode {
	DECLARE_ES5_CLASS(BiquadFilterNode, BiquadFilterNode);

  public:
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);

	explicit BiquadFilterNode(const Napi::CallbackInfo &info);
	~BiquadFilterNode();

	void _destroy();

  private:
	std::string _type;
	Napi::ObjectReference _frequency;
	Napi::ObjectReference _detune;
	Napi::ObjectReference _Q;
	Napi::ObjectReference _gain;

	JS_DECLARE_METHOD(BiquadFilterNode, destroy);
	JS_DECLARE_METHOD(BiquadFilterNode, getFrequencyResponse);

	JS_DECLARE_GETTER(BiquadFilterNode, type);
	JS_DECLARE_SETTER(BiquadFilterNode, type);
	JS_DECLARE_GETTER(BiquadFilterNode, frequency);
	JS_DECLARE_GETTER(BiquadFilterNode, detune);
	JS_DECLARE_GETTER(BiquadFilterNode, Q);
	JS_DECLARE_GETTER(BiquadFilterNode, gain);
};
