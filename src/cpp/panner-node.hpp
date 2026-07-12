#pragma once

#include "common.hpp"


class PannerNode : public CommonNode {
	DECLARE_ES5_CLASS(PannerNode, PannerNode);

  public:
	static void init(Napi::Env env, Napi::Object exports);

	explicit PannerNode(const Napi::CallbackInfo &info);
	~PannerNode();

	void _destroy();

  private:
	Napi::ObjectReference _positionX;
	Napi::ObjectReference _positionY;
	Napi::ObjectReference _positionZ;
	Napi::ObjectReference _orientationX;
	Napi::ObjectReference _orientationY;
	Napi::ObjectReference _orientationZ;

	JS_DECLARE_METHOD(PannerNode, destroy);
	JS_DECLARE_METHOD(PannerNode, setPosition);
	JS_DECLARE_METHOD(PannerNode, setOrientation);
	JS_DECLARE_METHOD(PannerNode, setVelocity);

	JS_DECLARE_GETTER(PannerNode, panningModel);
	JS_DECLARE_SETTER(PannerNode, panningModel);
	JS_DECLARE_GETTER(PannerNode, positionX);
	JS_DECLARE_GETTER(PannerNode, positionY);
	JS_DECLARE_GETTER(PannerNode, positionZ);
	JS_DECLARE_GETTER(PannerNode, orientationX);
	JS_DECLARE_GETTER(PannerNode, orientationY);
	JS_DECLARE_GETTER(PannerNode, orientationZ);
	JS_DECLARE_GETTER(PannerNode, distanceModel);
	JS_DECLARE_SETTER(PannerNode, distanceModel);
	JS_DECLARE_GETTER(PannerNode, refDistance);
	JS_DECLARE_SETTER(PannerNode, refDistance);
	JS_DECLARE_GETTER(PannerNode, maxDistance);
	JS_DECLARE_SETTER(PannerNode, maxDistance);
	JS_DECLARE_GETTER(PannerNode, rolloffFactor);
	JS_DECLARE_SETTER(PannerNode, rolloffFactor);
	JS_DECLARE_GETTER(PannerNode, coneInnerAngle);
	JS_DECLARE_SETTER(PannerNode, coneInnerAngle);
	JS_DECLARE_GETTER(PannerNode, coneOuterAngle);
	JS_DECLARE_SETTER(PannerNode, coneOuterAngle);
	JS_DECLARE_GETTER(PannerNode, coneOuterGain);
	JS_DECLARE_SETTER(PannerNode, coneOuterGain);
};
