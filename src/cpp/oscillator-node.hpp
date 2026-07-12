#pragma once

#include "common.hpp"


class OscillatorNode : public CommonNode {
	DECLARE_ES5_CLASS(OscillatorNode, OscillatorNode);

  public:
	static void init(Napi::Env env, Napi::Object exports);

	explicit OscillatorNode(const Napi::CallbackInfo &info);
	~OscillatorNode();

	void _destroy();

  private:
	std::string _type;
	Napi::ObjectReference _frequency;
	Napi::ObjectReference _detune;

	JS_DECLARE_METHOD(OscillatorNode, destroy);

	JS_DECLARE_METHOD(OscillatorNode, setPeriodicWave);

	JS_DECLARE_GETTER(OscillatorNode, type);
	JS_DECLARE_SETTER(OscillatorNode, type);

	JS_DECLARE_GETTER(OscillatorNode, frequency);

	JS_DECLARE_GETTER(OscillatorNode, detune);
};
