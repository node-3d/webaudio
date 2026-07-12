#pragma once

#include "common.hpp"


class DelayNode : public CommonNode {
	DECLARE_ES5_CLASS(DelayNode, DelayNode);

  public:
	static void init(Napi::Env env, Napi::Object exports);

	explicit DelayNode(const Napi::CallbackInfo &info);
	~DelayNode();

	void _destroy();

  private:
	Napi::ObjectReference _delayTime;

	JS_DECLARE_METHOD(DelayNode, destroy);

	JS_DECLARE_GETTER(DelayNode, delayTime);
};
