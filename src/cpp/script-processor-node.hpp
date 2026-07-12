#pragma once

#include "common.hpp"

#include "audio-node.hpp"


class ScriptProcessorNode : public CommonNode {
	DECLARE_ES5_CLASS(ScriptProcessorNode, ScriptProcessorNode);

  public:
	~ScriptProcessorNode();
	explicit ScriptProcessorNode(const Napi::CallbackInfo &info);

	static void init(Napi::Env env, Napi::Object exports);

	static bool isScriptProcessorNode(Napi::Object obj);

	// Destroy an instance from C++ land
	void _destroy();


  protected:
	ScriptProcessorNode();

	static Napi::FunctionReference _constructor;

	bool _isDestroyed;

	Napi::FunctionReference _onaudioprocess;
	int _bufferSize;


  private:
	JS_DECLARE_METHOD(ScriptProcessorNode, destroy);
	JS_DECLARE_GETTER(ScriptProcessorNode, isDestroyed);


	JS_DECLARE_GETTER(ScriptProcessorNode, onaudioprocess);
	JS_DECLARE_SETTER(ScriptProcessorNode, onaudioprocess);

	JS_DECLARE_GETTER(ScriptProcessorNode, bufferSize);
};
