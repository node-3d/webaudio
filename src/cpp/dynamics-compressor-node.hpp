#pragma once

#include "common.hpp"


class DynamicsCompressorNode : public CommonNode {
	DECLARE_ES5_CLASS(DynamicsCompressorNode, DynamicsCompressorNode);

  public:
	~DynamicsCompressorNode();
	explicit DynamicsCompressorNode(const Napi::CallbackInfo &info);

	static void init(Napi::Env env, Napi::Object exports);

	static bool isDynamicsCompressorNode(Napi::Object obj);

	// Destroy an instance from C++ land
	void _destroy();


  protected:
	DynamicsCompressorNode();

	static Napi::FunctionReference _constructor;

	bool _isDestroyed;

	Napi::ObjectReference _threshold;
	Napi::ObjectReference _knee;
	Napi::ObjectReference _ratio;
	float _reduction;
	Napi::ObjectReference _attack;
	Napi::ObjectReference _release;


  private:
	JS_DECLARE_METHOD(DynamicsCompressorNode, destroy);
	JS_DECLARE_GETTER(DynamicsCompressorNode, isDestroyed);


	JS_DECLARE_GETTER(DynamicsCompressorNode, threshold);

	JS_DECLARE_GETTER(DynamicsCompressorNode, knee);

	JS_DECLARE_GETTER(DynamicsCompressorNode, ratio);

	JS_DECLARE_GETTER(DynamicsCompressorNode, reduction);

	JS_DECLARE_GETTER(DynamicsCompressorNode, attack);

	JS_DECLARE_GETTER(DynamicsCompressorNode, release);
};
