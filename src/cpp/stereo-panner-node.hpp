#pragma once

#include "common.hpp"
#include "audio-node.hpp"


class StereoPannerNode : public CommonNode {
	DECLARE_ES5_CLASS(StereoPannerNode, StereoPannerNode);

  public:
	~StereoPannerNode();
	explicit StereoPannerNode(const Napi::CallbackInfo &info);

	static void init(Napi::Env env, Napi::Object exports);

	static bool isStereoPannerNode(Napi::Object obj);

	// Destroy an instance from C++ land
	void _destroy();


  protected:
	StereoPannerNode();

	static Napi::FunctionReference _constructor;

	bool _isDestroyed;

	Napi::ObjectReference _pan;


  private:
	JS_DECLARE_METHOD(StereoPannerNode, destroy);
	JS_DECLARE_GETTER(StereoPannerNode, isDestroyed);


	JS_DECLARE_GETTER(StereoPannerNode, pan);
};
