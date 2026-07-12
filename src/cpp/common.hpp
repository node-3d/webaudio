#pragma once

#include <memory>
#include <LabSound/LabSound.h>
#include <addon-tools.hpp>


class AudioContext;

#define PARAM_GETTER(CLASS, NAME)                                                                            \
	JS_IMPLEMENT_GETTER(CLASS, NAME) {                                                                       \
		THIS_CHECK;                                                                                          \
		RET_VALUE(_##NAME.Value());                                                                          \
	}

typedef std::shared_ptr<lab::AudioNode> NodePtr;
typedef std::shared_ptr<lab::AudioParam> ParamPtr;
typedef std::shared_ptr<lab::AudioSetting> SettingPtr;
typedef std::shared_ptr<lab::AudioContext> CtxPtr;
typedef std::shared_ptr<lab::AudioBus> BusPtr;
typedef std::shared_ptr<lab::AudioListener> ListenerPtr;

void _disconnectNode(AudioContext *context, NodePtr node);
void _disconnectParam(AudioContext *context, ParamPtr node);


struct Common {
	typedef std::function<void(Napi::Env, Napi::Function)> CallbackWrapper;

	static inline void CallJS(napi_env env, napi_value jsCallback, void * /* context */, void *data) {
		if (env == nullptr && jsCallback == nullptr) {
			return;
		}
		if (data != nullptr) {
			auto *callbackWrapper = static_cast<CallbackWrapper *>(data);
			(*callbackWrapper)(env, Napi::Function(env, jsCallback));
			delete callbackWrapper;
		} else if (jsCallback != nullptr) {
			Napi::Function(env, jsCallback).Call({});
		}
	}

	Common(Napi::Value that, const char *name) : _asyncCtx(that.Env(), name) {
		_that.Reset(that.As<Napi::Object>());
		_isDestroyed = false;

		// Create a ThreadSafeFunction
		Napi::Env env = that.Env();
		Napi::Object emitter = that.As<Napi::Object>();
		Napi::Function emit = emitter.Get("emit").As<Napi::Function>();
		napi_threadsafe_function tsfn;
		napi_status status;

		status = napi_create_threadsafe_function(
		    env, emit, Napi::Object(), JS_STR(name), 0, 1, nullptr, nullptr, nullptr, CallJS, &tsfn
		);
		if (status != napi_ok) {
			std::cerr << "Error: Failed to create a threadsafe function." << std::endl;
		}

		status = napi_unref_threadsafe_function(env, tsfn);

		if (status != napi_ok) {
			std::cerr << "Error: Failed to unref the threadsafe function." << std::endl;
		}

		_tsEmit = Napi::ThreadSafeFunction(tsfn);
	}

	~Common() {
		_destroy();
	}

	void emit(const char *name, int argc = 0, const Napi::Value *argv = nullptr) {
		DES_CHECK;
		eventEmit(_that.Value(), name, argc, argv);
	}

	void emitAsync(const char *name, int argc = 0, const Napi::Value *argv = nullptr) {
		_tsEmit.Acquire();

		Common *that = this;
		napi_status status =
		    _tsEmit.NonBlockingCall([that, name, argc, argv](Napi::Env env, Napi::Function emit) {
			    std::vector<napi_value> args;
			    args.push_back(JS_STR(name));
			    for (int i = 0; i < argc; i++) {
				    args.push_back(argv[i]);
			    }
			    emit.Call(that->_that.Value(), args);
		    });

		if (status != napi_ok) {
			std::cerr << "Error: could not call the threadsafe function." << std::endl;
		}

		_tsEmit.Release();
	}

	void _destroy() {
		DES_CHECK;
		_isDestroyed = true;
		_context.Reset();
		_that.Reset();
	}

	bool _isDestroyed;

	void reset(Napi::Object context);

	Napi::ObjectReference _that;
	Napi::ObjectReference _context;
	AudioContext *_contextVal;
	Napi::AsyncContext _asyncCtx;
	Napi::ThreadSafeFunction _tsEmit;
};


struct CommonNode : public Common {
	CommonNode(Napi::Value that, const char *name) : Common(that, name) {}

	~CommonNode() {
		_destroy();
	}

	void _destroy() {
		DES_CHECK;
		// _disconnectNode(_contextVal, _impl);
		_impl.reset();
		Common::_destroy();
	}

	NodePtr getNode() const {
		return _impl;
	}

	void reset(Napi::Object context, NodePtr node) {
		Common::reset(context);
		_impl = node;
	}

	NodePtr _impl;
};


struct CommonParam : public Common {
	CommonParam(Napi::Value that, const char *name) : Common(that, name) {}

	~CommonParam() {
		_destroy();
	}

	void _destroy() {
		DES_CHECK;
		// _disconnectParam(_contextVal, _impl);
		_impl.reset();
		Common::_destroy();
	}

	ParamPtr getParam() const {
		return _impl;
	}

	void reset(Napi::Object context, ParamPtr param) {
		Common::reset(context);
		_impl = param;
	}

	ParamPtr _impl;
};


struct CommonSetting : public Common {
	CommonSetting(Napi::Value that, const char *name) : Common(that, name) {}

	~CommonSetting() {
		_destroy();
	}

	void _destroy() {
		DES_CHECK;
		_impl.reset();
		Common::_destroy();
	}

	SettingPtr getSetting() const {
		return _impl;
	}

	void reset(Napi::Object context, SettingPtr setting) {
		Common::reset(context);
		_impl = setting;
	}

	SettingPtr _impl;
};


struct CommonCtx : public Common {
	CommonCtx(Napi::Value that, const char *name) : Common(that, name) {}

	~CommonCtx() {
		_destroy();
	}

	void _destroy() {
		DES_CHECK;
		_impl.reset();
		Common::_destroy();
	}

	CtxPtr getCtx() const {
		return _impl;
	}

	void reset(CtxPtr ctx) {
		_impl = ctx;
	}

	CtxPtr _impl;
};


struct CommonBus : public Common {
	CommonBus(Napi::Value that, const char *name) : Common(that, name) {}

	~CommonBus() {
		_destroy();
	}

	void _destroy() {
		DES_CHECK;

		_impl.reset();

		Common::_destroy();
	}

	BusPtr getBus() const {
		return _impl;
	}

	void reset(Napi::Object context, BusPtr bus) {
		Common::reset(context);
		_impl = bus;
	}

	BusPtr _impl;
};


struct CommonListener : public Common {
	CommonListener(Napi::Value that, const char *name) : Common(that, name) {}

	~CommonListener() {
		_destroy();
	}

	void _destroy() {
		DES_CHECK;
		_impl = nullptr;
		Common::_destroy();
	}

	ListenerPtr getListener() const {
		return _impl;
	}

	void reset(Napi::Object context, ListenerPtr listener) {
		Common::reset(context);
		_impl = listener;
	}

	ListenerPtr _impl;
};
