#pragma once

#include "common.hpp"
#include "audio-node.hpp"


class ConvolverNode : public CommonNode {
	DECLARE_ES5_CLASS(ConvolverNode, ConvolverNode);

  public:
	static void init(Napi::Env env, Napi::Object exports);

	explicit ConvolverNode(const Napi::CallbackInfo &info);
	~ConvolverNode();

	void _destroy();

  private:
	Napi::ObjectReference _buffer;

	JS_DECLARE_METHOD(ConvolverNode, destroy);

	JS_DECLARE_GETTER(ConvolverNode, buffer);
	JS_DECLARE_SETTER(ConvolverNode, buffer);

	JS_DECLARE_GETTER(ConvolverNode, normalize);
	JS_DECLARE_SETTER(ConvolverNode, normalize);
};
