#include "common.cpp"
#include "analyser-node.cpp"
#include "audio-buffer.cpp"
#include "audio-buffer-source-node.cpp"
#include "audio-context.cpp"
#include "audio-destination-node.cpp"
#include "audio-listener.cpp"
#include "audio-node.cpp"
#include "audio-param.cpp"
#include "audio-setting.cpp"
// #include "audio-processing-event.cpp"
#include "audio-scheduled-source-node.cpp"
#include "base-audio-context.cpp"
#include "biquad-filter-node.cpp"
// #include "channel-merger-node.cpp"
// #include "channel-splitter-node.cpp"
// #include "constant-source-node.cpp"
#include "convolver-node.cpp"
#include "delay-node.cpp"
// #include "dynamics-compressor-node.cpp"
#include "gain-node.cpp"
// #include "iir-filter-node.cpp"
// #include "media-element-audio-source-node.cpp"
// #include "media-stream-audio-destination-node.cpp"
// #include "media-stream-audio-source-node.cpp"
// #include "offline-audio-completion-event.cpp"
// #include "offline-audio-context.cpp"
#include "oscillator-node.cpp"
#include "panner-node.cpp"
// #include "periodic-wave.cpp"
// #include "script-processor-node.cpp"
// #include "stereo-panner-node.cpp"
// #include "wave-shaper-node.cpp"


Napi::Object initModule(Napi::Env env, Napi::Object exports) {
	log_set_level(LOGLEVEL_WARN);

	BaseAudioContext::init(env, exports);
	AudioContext::init(env, exports);
	// OfflineAudioContext::init(env, exports);

	AudioBuffer::init(env, exports);
	AudioListener::init(env, exports);

	AudioParam::init(env, exports);
	AudioSetting::init(env, exports);

	// PeriodicWave::init(env, exports);
	// OfflineAudioCompletionEvent::init(env, exports);

	AudioNode::init(env, exports);

	AudioDestinationNode::init(env, exports);
	AudioScheduledSourceNode::init(env, exports);

	AnalyserNode::init(env, exports);
	AudioBufferSourceNode::init(env, exports);

	BiquadFilterNode::init(env, exports);
	// ChannelMergerNode::init(env, exports);
	// ChannelSplitterNode::init(env, exports);
	// ConstantSourceNode::init(env, exports);
	ConvolverNode::init(env, exports);
	DelayNode::init(env, exports);
	// DynamicsCompressorNode::init(env, exports);
	GainNode::init(env, exports);
	// IIRFilterNode::init(env, exports);
	// MediaElementAudioSourceNode::init(env, exports);
	// MediaStreamAudioDestinationNode::init(env, exports);
	// MediaStreamAudioSourceNode::init(env, exports);
	OscillatorNode::init(env, exports);
	PannerNode::init(env, exports);
	// ScriptProcessorNode::init(env, exports);
	// StereoPannerNode::init(env, exports);
	// WaveShaperNode::init(env, exports);

	return exports;
}


NODE_API_MODULE(webaudio, initModule)
