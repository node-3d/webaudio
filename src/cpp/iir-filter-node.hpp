#pragma once

#include "common.hpp"


class IIRFilterNode : public CommonNode {
	DECLARE_ES5_CLASS(IIRFilterNode, IIRFilterNode);

  public:
	~IIRFilterNode();
	explicit IIRFilterNode(const Napi::CallbackInfo &info);

	static void init(Napi::Env env, Napi::Object exports);

	static bool isIIRFilterNode(Napi::Object obj);

	// Destroy an instance from C++ land
	void _destroy();


  protected:
	IIRFilterNode();

	static Napi::FunctionReference _constructor;

	bool _isDestroyed;

  private:
	JS_DECLARE_METHOD(IIRFilterNode, destroy);
	JS_DECLARE_GETTER(IIRFilterNode, isDestroyed);

	JS_DECLARE_METHOD(IIRFilterNode, getFrequencyResponse);
};
