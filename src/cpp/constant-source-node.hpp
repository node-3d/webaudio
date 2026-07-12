#pragma once

#include "common.hpp"
#include "audio-scheduled-source-node.hpp"


class ConstantSourceNode : public AudioScheduledSourceNode {
  public:
	explicit ConstantSourceNode(const Napi::CallbackInfo &info);
	~ConstantSourceNode();

	static void init(Napi::Env env, Napi::Object exports);

	void _destroy();

  protected:
	ConstantSourceNode();

	static Napi::FunctionReference _constructor;

	bool _isDestroyed;

	Napi::ObjectReference _offset;


  private:
	JS_DECLARE_METHOD(ConstantSourceNode, destroy);
	JS_DECLARE_GETTER(ConstantSourceNode, isDestroyed);

	JS_DECLARE_GETTER(ConstantSourceNode, offset);
};
