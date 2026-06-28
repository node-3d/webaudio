import { inherits, inspect } from "node:util";
import node_events from "node:events";
import { createRequire } from "node:module";
import { getBin } from "@node-3d/addon-tools";
import "@node-3d/segfault";
import { hrtf } from "@node-3d/deps-labsound";
const loadAddon = createRequire(import.meta.url);
const native_native = loadAddon(`../${getBin()}/webaudio.node`);
function _to_primitive(input, hint) {
    if ("object" !== _type_of(input) || null === input) return input;
    var prim = input[Symbol.toPrimitive];
    if (void 0 !== prim) {
        var res = prim.call(input, hint || "default");
        if ("object" !== _type_of(res)) return res;
        throw new TypeError("@@toPrimitive must return a primitive value.");
    }
    return ("string" === hint ? String : Number)(input);
}
function _to_property_key(arg) {
    var key = _to_primitive(arg, "string");
    return "symbol" === _type_of(key) ? key : String(key);
}
function _type_of(obj) {
    return obj && "u" > typeof Symbol && obj.constructor === Symbol ? "symbol" : typeof obj;
}
let audio_buffer_computedKey;
const { AudioBuffer: AudioBuffer } = native_native;
inherits(AudioBuffer, node_events);
audio_buffer_computedKey = _to_property_key(inspect.custom);
class JsAudioBuffer extends AudioBuffer {
    [audio_buffer_computedKey]() {
        return this.toString();
    }
    toString() {
        return 'AudioBuffer {}';
    }
}
const setEventCallbacks = (emitter, eventName, callbacks)=>{
    if (!callbacks) return void emitter.removeAllListeners(eventName);
    if ('function' == typeof callbacks) return void emitter.on(eventName, callbacks);
    for (const callback of callbacks)emitter.on(eventName, callback);
};
const { AudioNode: AudioNode } = native_native;
inherits(AudioNode, node_events);
const nonGcRefs = new Set();
const audio_node_JsAudioNode = function(ctx, node) {
    AudioNode.call(this, ctx, node);
    nonGcRefs.add(this);
    this.on('destroy', ()=>{
        nonGcRefs.delete(this);
    });
};
const audioNodePrototype = {
    get onerror () {
        return this.listeners('error');
    },
    set onerror (cb){
        setEventCallbacks(this, 'error', cb);
    },
    get onended () {
        return this.listeners('ended');
    },
    set onended (cb){
        setEventCallbacks(this, 'ended', cb);
    },
    [inspect.custom] () {
        return this.toString();
    },
    toString () {
        return 'AudioNode {}';
    }
};
audio_node_JsAudioNode.prototype = audioNodePrototype;
inherits(audio_node_JsAudioNode, AudioNode);
const { AudioDestinationNode: AudioDestinationNode } = native_native;
inherits(AudioDestinationNode, audio_node_JsAudioNode);
const audio_destination_node_JsAudioDestinationNode = function(ctx, node) {
    AudioDestinationNode.call(this, ctx, node);
};
audio_destination_node_JsAudioDestinationNode.prototype = {
    [inspect.custom] () {
        return this.toString();
    },
    toString () {
        return 'AudioDestinationNode {}';
    }
};
inherits(audio_destination_node_JsAudioDestinationNode, AudioDestinationNode);
function audio_param_to_primitive(input, hint) {
    if ("object" !== audio_param_type_of(input) || null === input) return input;
    var prim = input[Symbol.toPrimitive];
    if (void 0 !== prim) {
        var res = prim.call(input, hint || "default");
        if ("object" !== audio_param_type_of(res)) return res;
        throw new TypeError("@@toPrimitive must return a primitive value.");
    }
    return ("string" === hint ? String : Number)(input);
}
function audio_param_to_property_key(arg) {
    var key = audio_param_to_primitive(arg, "string");
    return "symbol" === audio_param_type_of(key) ? key : String(key);
}
function audio_param_type_of(obj) {
    return obj && "u" > typeof Symbol && obj.constructor === Symbol ? "symbol" : typeof obj;
}
let audio_param_computedKey;
const { AudioParam: AudioParam } = native_native;
inherits(AudioParam, node_events);
audio_param_computedKey = audio_param_to_property_key(inspect.custom);
class JsAudioParam extends AudioParam {
    get onerror() {
        return this.listeners('error');
    }
    set onerror(cb1) {
        setEventCallbacks(this, 'error', cb1);
    }
    get onended() {
        return this.listeners('ended');
    }
    set onended(cb1) {
        setEventCallbacks(this, 'ended', cb1);
    }
    [audio_param_computedKey]() {
        return this.toString();
    }
    toString() {
        return `AudioParam { ${this.value} }`;
    }
}
function audio_listener_to_primitive(input, hint) {
    if ("object" !== audio_listener_type_of(input) || null === input) return input;
    var prim = input[Symbol.toPrimitive];
    if (void 0 !== prim) {
        var res = prim.call(input, hint || "default");
        if ("object" !== audio_listener_type_of(res)) return res;
        throw new TypeError("@@toPrimitive must return a primitive value.");
    }
    return ("string" === hint ? String : Number)(input);
}
function audio_listener_to_property_key(arg) {
    var key = audio_listener_to_primitive(arg, "string");
    return "symbol" === audio_listener_type_of(key) ? key : String(key);
}
function audio_listener_type_of(obj) {
    return obj && "u" > typeof Symbol && obj.constructor === Symbol ? "symbol" : typeof obj;
}
let audio_listener_computedKey;
const { AudioListener: AudioListener } = native_native;
inherits(AudioListener, node_events);
audio_listener_computedKey = audio_listener_to_property_key(inspect.custom);
class JsAudioListener extends AudioListener {
    constructor(ctx, listener){
        super(ctx, listener, JsAudioParam);
    }
    [audio_listener_computedKey]() {
        return this.toString();
    }
    toString() {
        return 'AudioListener {}';
    }
}
const { AudioScheduledSourceNode: AudioScheduledSourceNode } = native_native;
inherits(AudioScheduledSourceNode, audio_node_JsAudioNode);
const audio_scheduled_source_node_JsAudioScheduledSourceNode = function(ctx, node) {
    AudioScheduledSourceNode.call(this, ctx, node);
};
audio_scheduled_source_node_JsAudioScheduledSourceNode.prototype = {
    [inspect.custom] () {
        return this.toString();
    },
    toString () {
        return 'AudioScheduledSourceNode {}';
    }
};
inherits(audio_scheduled_source_node_JsAudioScheduledSourceNode, AudioScheduledSourceNode);
function nodes_to_primitive(input, hint) {
    if ("object" !== nodes_type_of(input) || null === input) return input;
    var prim = input[Symbol.toPrimitive];
    if (void 0 !== prim) {
        var res = prim.call(input, hint || "default");
        if ("object" !== nodes_type_of(res)) return res;
        throw new TypeError("@@toPrimitive must return a primitive value.");
    }
    return ("string" === hint ? String : Number)(input);
}
function nodes_to_property_key(arg) {
    var key = nodes_to_primitive(arg, "string");
    return "symbol" === nodes_type_of(key) ? key : String(key);
}
function nodes_type_of(obj) {
    return obj && "u" > typeof Symbol && obj.constructor === Symbol ? "symbol" : typeof obj;
}
const baseDescs = [
    'AnalyserNode',
    'BiquadFilterNode',
    'ConvolverNode',
    'DelayNode',
    'GainNode',
    'PannerNode'
];
const scheduledDescs = [
    'AudioBufferSourceNode',
    'OscillatorNode'
];
const subclassBase = (name, SuperNode)=>{
    let _computedKey;
    const SuperClass = native_native[name];
    inherits(SuperClass, SuperNode);
    _computedKey = nodes_to_property_key(inspect.custom);
    class JsNode extends SuperClass {
        _opts;
        constructor(ctx, opts = {}){
            super(ctx, JsAudioParam, opts);
            this._opts = opts;
        }
        [_computedKey]() {
            return this.toString();
        }
        toString() {
            return `${name} ${JSON.stringify(this._opts, null, '\t')}`;
        }
    }
    return JsNode;
};
const baseNodes = {
    AudioScheduledSourceNode: audio_scheduled_source_node_JsAudioScheduledSourceNode
};
for (const name of baseDescs)baseNodes[name] = subclassBase(name, audio_node_JsAudioNode);
const scheduledNodes = {};
for (const name of scheduledDescs)scheduledNodes[name] = subclassBase(name, audio_scheduled_source_node_JsAudioScheduledSourceNode);
const nodes = {
    ...baseNodes,
    ...scheduledNodes
};
const { AudioScheduledSourceNode: nodes_AudioScheduledSourceNode, AnalyserNode: AnalyserNode, BiquadFilterNode: BiquadFilterNode, ConvolverNode: ConvolverNode, DelayNode: DelayNode, GainNode: GainNode, PannerNode: PannerNode, AudioBufferSourceNode: AudioBufferSourceNode, OscillatorNode: OscillatorNode } = nodes;
const BaseAudioContext = native_native.BaseAudioContext;
inherits(BaseAudioContext, node_events);
BaseAudioContext.hrtf = hrtf;
const base_audio_context_JsBaseAudioContext = function(ctx, sampleRate = -1) {
    BaseAudioContext.call(this, ctx, sampleRate);
    this._initListener(audio_destination_node_JsAudioDestinationNode, JsAudioListener, sampleRate);
};
const baseAudioContextPrototype = {
    get onerror () {
        return this.listeners('error');
    },
    set onerror (cb){
        setEventCallbacks(this, 'error', cb);
    },
    get onstatechange () {
        return this.listeners('statechange');
    },
    set onstatechange (cb){
        setEventCallbacks(this, 'statechange', cb);
    },
    [inspect.custom] () {
        return this.toString();
    },
    toString () {
        return 'BaseAudioContext {}';
    },
    decodeAudioData (audioData, successCallback) {
        BaseAudioContext.prototype.decodeAudioData.call(this, audioData, successCallback, JsAudioBuffer);
    },
    createAnalyser (opts = {}) {
        return new nodes.AnalyserNode(this, opts);
    },
    createBiquadFilter (opts = {}) {
        return new nodes.BiquadFilterNode(this, opts);
    },
    createBuffer (opts = {}) {
        return new JsAudioBuffer(this, opts);
    },
    createBufferSource (opts = {}) {
        return new nodes.AudioBufferSourceNode(this, opts);
    },
    createChannelMerger (opts = {}) {
        return new nodes.ChannelMergerNode(this, opts);
    },
    createChannelSplitter (opts = {}) {
        return new nodes.ChannelSplitterNode(this, opts);
    },
    createConstantSource (opts = {}) {
        return new nodes.ConstantSourceNode(this, opts);
    },
    createConvolver (opts = {}) {
        return new nodes.ConvolverNode(this, opts);
    },
    createDelay (maxDelayTime = 1) {
        return new nodes.DelayNode(this, {
            maxDelayTime
        });
    },
    createDynamicsCompressor (opts = {}) {
        return new nodes.DynamicsCompressorNode(this, opts);
    },
    createGain (opts = {}) {
        return new nodes.GainNode(this, opts);
    },
    createIIRFilter (opts = {}) {
        return new nodes.IIRFilterNode(this, opts);
    },
    createOscillator (opts = {}) {
        return new nodes.OscillatorNode(this, opts);
    },
    createPanner (opts = {}) {
        return new nodes.PannerNode(this, opts);
    },
    createPeriodicWave (opts = {}) {
        return new nodes.PeriodicWaveNode(this, opts);
    },
    createScriptProcessor (opts = {}) {
        return new nodes.ScriptProcessorNode(this, opts);
    },
    createStereoPanner (opts = {}) {
        return new nodes.StereoPannerNode(this, opts);
    },
    createWaveShaper (opts = {}) {
        return new nodes.WaveShaperNode(this, opts);
    }
};
base_audio_context_JsBaseAudioContext.prototype = baseAudioContextPrototype;
inherits(base_audio_context_JsBaseAudioContext, BaseAudioContext);
function audio_context_to_primitive(input, hint) {
    if ("object" !== audio_context_type_of(input) || null === input) return input;
    var prim = input[Symbol.toPrimitive];
    if (void 0 !== prim) {
        var res = prim.call(input, hint || "default");
        if ("object" !== audio_context_type_of(res)) return res;
        throw new TypeError("@@toPrimitive must return a primitive value.");
    }
    return ("string" === hint ? String : Number)(input);
}
function audio_context_to_property_key(arg) {
    var key = audio_context_to_primitive(arg, "string");
    return "symbol" === audio_context_type_of(key) ? key : String(key);
}
function audio_context_type_of(obj) {
    return obj && "u" > typeof Symbol && obj.constructor === Symbol ? "symbol" : typeof obj;
}
let audio_context_computedKey;
const { AudioContext: AudioContext } = native_native;
inherits(AudioContext, base_audio_context_JsBaseAudioContext);
audio_context_computedKey = audio_context_to_property_key(inspect.custom);
class JsAudioContext extends AudioContext {
    constructor(opts = {}){
        if (void 0 === opts.sampleRate) super();
        else super(opts.sampleRate);
    }
    [audio_context_computedKey]() {
        return this.toString();
    }
    toString() {
        return 'AudioContext {}';
    }
}
const WrappedAudioContext = JsAudioContext;
export { AnalyserNode, AudioBufferSourceNode, BiquadFilterNode, ConvolverNode, DelayNode, GainNode, JsAudioBuffer as AudioBuffer, JsAudioParam as AudioParam, OscillatorNode, PannerNode, WrappedAudioContext as AudioContext, nodes, nodes_AudioScheduledSourceNode as AudioScheduledSourceNode };
