#include "audio-listener.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


IMPLEMENT_ES5_CLASS(AudioListener);

void AudioListener::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(setOrientation);
	JS_ASSIGN_METHOD(setPosition);
	JS_ASSIGN_GETTER(upZ);
	JS_ASSIGN_GETTER(upY);
	JS_ASSIGN_GETTER(upX);
	JS_ASSIGN_GETTER(forwardZ);
	JS_ASSIGN_GETTER(forwardY);
	JS_ASSIGN_GETTER(forwardX);
	JS_ASSIGN_GETTER(positionZ);
	JS_ASSIGN_GETTER(positionY);
	JS_ASSIGN_GETTER(positionX);
	JS_ASSIGN_METHOD(destroy);

	exports.Set("AudioListener", ctor);
}


AudioListener::AudioListener(const Napi::CallbackInfo &info) : CommonListener(info.This(), "AudioListener") {
	NAPI_ENV;
	super(info);

	Napi::Object context = info[0].As<Napi::Object>();
	Napi::External<void> extListener = info[1].As<Napi::External<void>>();

	ListenerPtr *listener = reinterpret_cast<ListenerPtr *>(extListener.Data());

	reset(context, *listener);

	Napi::Function paramCtor = info[2].As<Napi::Function>();

	napi_value argv[2];
	argv[0] = context;

	ParamPtr positionXParam = _impl->positionX();
	argv[1] = JS_EXT(&positionXParam);
	_positionX.Reset(paramCtor.New(2, argv), 1);

	ParamPtr positionYParam = _impl->positionY();
	argv[1] = JS_EXT(&positionYParam);
	_positionY.Reset(paramCtor.New(2, argv), 1);

	ParamPtr positionZParam = _impl->positionZ();
	argv[1] = JS_EXT(&positionZParam);
	_positionZ.Reset(paramCtor.New(2, argv), 1);

	ParamPtr forwardXParam = _impl->forwardX();
	argv[1] = JS_EXT(&forwardXParam);
	_forwardX.Reset(paramCtor.New(2, argv), 1);

	ParamPtr forwardYParam = _impl->forwardY();
	argv[1] = JS_EXT(&forwardYParam);
	_forwardY.Reset(paramCtor.New(2, argv), 1);

	ParamPtr forwardZParam = _impl->forwardZ();
	argv[1] = JS_EXT(&forwardZParam);
	_forwardZ.Reset(paramCtor.New(2, argv), 1);

	ParamPtr upXParam = _impl->upX();
	argv[1] = JS_EXT(&upXParam);
	_upX.Reset(paramCtor.New(2, argv), 1);

	ParamPtr upYParam = _impl->upY();
	argv[1] = JS_EXT(&upYParam);
	_upY.Reset(paramCtor.New(2, argv), 1);

	ParamPtr upZParam = _impl->upZ();
	argv[1] = JS_EXT(&upZParam);
	_upZ.Reset(paramCtor.New(2, argv), 1);
}


AudioListener::~AudioListener() {
	_destroy();
}


void AudioListener::_destroy() {
	DES_CHECK;
	_positionX.Reset();
	_positionY.Reset();
	_positionZ.Reset();
	_forwardX.Reset();
	_forwardY.Reset();
	_forwardZ.Reset();
	_upX.Reset();
	_upY.Reset();
	_upZ.Reset();
	CommonListener::_destroy();
}


PARAM_GETTER(AudioListener, positionX);
PARAM_GETTER(AudioListener, positionY);
PARAM_GETTER(AudioListener, positionZ);
PARAM_GETTER(AudioListener, forwardX);
PARAM_GETTER(AudioListener, forwardY);
PARAM_GETTER(AudioListener, forwardZ);
PARAM_GETTER(AudioListener, upX);
PARAM_GETTER(AudioListener, upY);
PARAM_GETTER(AudioListener, upZ);


JS_IMPLEMENT_METHOD(AudioListener, setPosition) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);

	_impl->setPosition(x, y, z);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(AudioListener, setOrientation) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	REQ_FLOAT_ARG(3, xUp);
	REQ_FLOAT_ARG(4, yUp);
	REQ_FLOAT_ARG(5, zUp);

	_impl->setOrientation(x, y, z, xUp, yUp, zUp);
	RET_UNDEFINED;
}

JS_IMPLEMENT_METHOD(AudioListener, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
