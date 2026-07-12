#pragma once

#include "common.hpp"


class MediaElementAudioSourceNode : public CommonNode {
	DECLARE_ES5_CLASS(MediaElementAudioSourceNode, MediaElementAudioSourceNode);

  public:
	~MediaElementAudioSourceNode();
	explicit MediaElementAudioSourceNode(const Napi::CallbackInfo &info);

	static void init(Napi::Env env, Napi::Object exports);

	static bool isMediaElementAudioSourceNode(Napi::Object obj);

	// Destroy an instance from C++ land
	void _destroy();


  protected:
	MediaElementAudioSourceNode();

	static Napi::FunctionReference _constructor;

	bool _isDestroyed;

	Napi::ObjectReference _mediaElement;


  private:
	JS_DECLARE_METHOD(MediaElementAudioSourceNode, destroy);
	JS_DECLARE_GETTER(MediaElementAudioSourceNode, isDestroyed);


	JS_DECLARE_GETTER(MediaElementAudioSourceNode, mediaElement);
};
