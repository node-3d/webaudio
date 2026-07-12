#pragma once

#include "common.hpp"
#include "audio-node.hpp"


class WaveShaperNode : public CommonNode {
	DECLARE_ES5_CLASS(WaveShaperNode, WaveShaperNode);

  public:
	~WaveShaperNode();
	explicit WaveShaperNode(const Napi::CallbackInfo &info);

	static void init(Napi::Env env, Napi::Object exports);


  protected:
	WaveShaperNode();

	Napi::ObjectReference _curve;
	std::string _oversample;


  private:
	JS_DECLARE_GETTER(WaveShaperNode, curve);
	JS_DECLARE_SETTER(WaveShaperNode, curve);

	JS_DECLARE_GETTER(WaveShaperNode, oversample);
	JS_DECLARE_SETTER(WaveShaperNode, oversample);
};
