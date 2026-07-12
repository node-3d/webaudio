#include "panner-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


inline std::string fromDistanceModel(lab::PannerNode::DistanceModel mode) {
	if (mode == lab::PannerNode::LINEAR_DISTANCE) {
		return "linear";
	} else if (mode == lab::PannerNode::INVERSE_DISTANCE) {
		return "inverse";
	} else {
		return "exponential";
	}
}


inline lab::PannerNode::DistanceModel toDistanceModel(const std::string &mode) {
	if (mode == "linear") {
		return lab::PannerNode::LINEAR_DISTANCE;
	} else if (mode == "inverse") {
		return lab::PannerNode::INVERSE_DISTANCE;
	} else {
		return lab::PannerNode::EXPONENTIAL_DISTANCE;
	}
}


inline const char *fromPanningModel(lab::PanningModel mode) {
	if (mode == lab::PanningModel::EQUALPOWER) {
		return "equalpower";
	} else {
		return "HRTF";
	}
}


inline lab::PanningModel toPanningModel(const std::string &mode) {
	if (mode == "equalpower") {
		return lab::PanningModel::EQUALPOWER;
	} else {
		return lab::PanningModel::HRTF;
	}
}


IMPLEMENT_ES5_CLASS(PannerNode);

void PannerNode::init(Napi::Env env, Napi::Object exports) {
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_SETTER(coneOuterGain);
	JS_ASSIGN_SETTER(coneOuterAngle);
	JS_ASSIGN_SETTER(coneInnerAngle);
	JS_ASSIGN_SETTER(rolloffFactor);
	JS_ASSIGN_SETTER(maxDistance);
	JS_ASSIGN_SETTER(refDistance);
	JS_ASSIGN_SETTER(distanceModel);
	JS_ASSIGN_SETTER(panningModel);
	JS_ASSIGN_METHOD(setVelocity);
	JS_ASSIGN_METHOD(setOrientation);
	JS_ASSIGN_METHOD(setPosition);
	JS_ASSIGN_GETTER(orientationZ);
	JS_ASSIGN_GETTER(orientationY);
	JS_ASSIGN_GETTER(orientationX);
	JS_ASSIGN_GETTER(positionZ);
	JS_ASSIGN_GETTER(positionY);
	JS_ASSIGN_GETTER(positionX);
	JS_ASSIGN_METHOD(destroy);

	exports.Set("PannerNode", ctor);
}


PannerNode::PannerNode(const Napi::CallbackInfo &info) : CommonNode(info.This(), "PannerNode") {
	NAPI_ENV;
	Napi::Object context = info[0].As<Napi::Object>();
	Napi::Function paramCtor = info[1].As<Napi::Function>();

	AudioContext *contextUnwrap = AudioContext::unwrap(context);
	lab::AudioContext *contextLab = contextUnwrap->getCtx().get();
	reset(context, std::make_shared<lab::PannerNode>(*contextLab));

	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	napi_value argv[2];
	argv[0] = context;

	ParamPtr positionXParam = node->positionX();
	argv[1] = JS_EXT(&positionXParam);
	_positionX.Reset(paramCtor.New(2, argv), 1);

	ParamPtr positionYParam = node->positionY();
	argv[1] = JS_EXT(&positionYParam);
	_positionY.Reset(paramCtor.New(2, argv), 1);

	ParamPtr positionZParam = node->positionZ();
	argv[1] = JS_EXT(&positionZParam);
	_positionZ.Reset(paramCtor.New(2, argv), 1);

	ParamPtr orientationXParam = node->orientationX();
	argv[1] = JS_EXT(&orientationXParam);
	_orientationX.Reset(paramCtor.New(2, argv), 1);

	ParamPtr orientationYParam = node->orientationY();
	argv[1] = JS_EXT(&orientationYParam);
	_orientationY.Reset(paramCtor.New(2, argv), 1);

	ParamPtr orientationZParam = node->orientationZ();
	argv[1] = JS_EXT(&orientationZParam);
	_orientationZ.Reset(paramCtor.New(2, argv), 1);

	argv[1] = JS_EXT(&_impl);
	super(info, 2, argv);
}


PannerNode::~PannerNode() {
	_destroy();
}


void PannerNode::_destroy() {
	DES_CHECK;
	_positionX.Reset();
	_positionY.Reset();
	_positionZ.Reset();
	_orientationX.Reset();
	_orientationY.Reset();
	_orientationZ.Reset();

	CommonNode::_destroy();
}


// ------ Methods and props


JS_IMPLEMENT_METHOD(PannerNode, setPosition) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);

	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setPosition(x, y, z);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(PannerNode, setOrientation) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);

	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setOrientation(lab::FloatPoint3D(x, y, z));
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(PannerNode, setVelocity) {
	THIS_CHECK;
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);

	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setVelocity(x, y, z);
	RET_UNDEFINED;
}

JS_IMPLEMENT_GETTER(PannerNode, panningModel) {
	THIS_CHECK;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	RET_VALUE(JS_STR(fromPanningModel(node->panningModel())));
}

JS_IMPLEMENT_SETTER(PannerNode, panningModel) {
	THIS_CHECK;
	SETTER_STR_ARG;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setPanningModel(toPanningModel(v.c_str()));

	emit("panningModel", 1, &value);
	RET_UNDEFINED;
}

PARAM_GETTER(PannerNode, positionX);
PARAM_GETTER(PannerNode, positionY);
PARAM_GETTER(PannerNode, positionZ);
PARAM_GETTER(PannerNode, orientationX);
PARAM_GETTER(PannerNode, orientationY);
PARAM_GETTER(PannerNode, orientationZ);

JS_IMPLEMENT_GETTER(PannerNode, distanceModel) {
	THIS_CHECK;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	RET_VALUE(JS_STR(fromDistanceModel(node->distanceModel())));
}

JS_IMPLEMENT_SETTER(PannerNode, distanceModel) {
	THIS_CHECK;
	SETTER_STR_ARG;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setDistanceModel(toDistanceModel(v.c_str()));

	emit("distanceModel", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(PannerNode, refDistance) {
	THIS_CHECK;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	RET_NUM(node->refDistance());
}

JS_IMPLEMENT_SETTER(PannerNode, refDistance) {
	THIS_CHECK;
	SETTER_DOUBLE_ARG;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setRefDistance(static_cast<float>(v));

	emit("refDistance", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(PannerNode, maxDistance) {
	THIS_CHECK;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	RET_NUM(node->maxDistance());
}

JS_IMPLEMENT_SETTER(PannerNode, maxDistance) {
	THIS_CHECK;
	SETTER_DOUBLE_ARG;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setMaxDistance(static_cast<float>(v));

	emit("maxDistance", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(PannerNode, rolloffFactor) {
	THIS_CHECK;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	RET_NUM(node->rolloffFactor());
}

JS_IMPLEMENT_SETTER(PannerNode, rolloffFactor) {
	THIS_CHECK;
	SETTER_DOUBLE_ARG;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setRolloffFactor(static_cast<float>(v));

	emit("rolloffFactor", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(PannerNode, coneInnerAngle) {
	THIS_CHECK;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	RET_NUM(node->coneInnerAngle());
}

JS_IMPLEMENT_SETTER(PannerNode, coneInnerAngle) {
	THIS_CHECK;
	SETTER_DOUBLE_ARG;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setConeInnerAngle(static_cast<float>(v));

	emit("coneInnerAngle", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(PannerNode, coneOuterAngle) {
	THIS_CHECK;

	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	RET_NUM(node->coneOuterAngle());
}

JS_IMPLEMENT_SETTER(PannerNode, coneOuterAngle) {
	THIS_CHECK;
	SETTER_DOUBLE_ARG;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setConeOuterAngle(static_cast<float>(v));

	emit("coneOuterAngle", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_GETTER(PannerNode, coneOuterGain) {
	THIS_CHECK;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	RET_NUM(node->coneOuterGain());
}

JS_IMPLEMENT_SETTER(PannerNode, coneOuterGain) {
	THIS_CHECK;
	SETTER_DOUBLE_ARG;
	lab::PannerNode *node = static_cast<lab::PannerNode *>(_impl.get());

	node->setConeOuterGain(static_cast<float>(v));

	emit("coneOuterGain", 1, &value);
	RET_UNDEFINED;
}


JS_IMPLEMENT_METHOD(PannerNode, destroy) {
	THIS_CHECK;
	emit("destroy");
	_destroy();
	RET_UNDEFINED;
}
