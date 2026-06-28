import type { EventEmitter } from 'node:events';
import '@node-3d/segfault';
import '@node-3d/deps-labsound';
export type TAudioEvent = Readonly<{
    type: string;
    [key: string]: unknown;
}>;
export type TAudioEventCallback<T extends TAudioEvent = TAudioEvent> = (event: T) => boolean | undefined;
export type TAudioEventCallbackList<T extends TAudioEvent = TAudioEvent> = TAudioEventCallback<T> | readonly TAudioEventCallback<T>[] | null | undefined;
export type TAudioContextState = 'closed' | 'interrupted' | 'running' | 'suspended';
export type TChannelCountMode = 'clamped-max' | 'explicit' | 'max';
export type TChannelInterpretation = 'discrete' | 'speakers';
export type TDistanceModel = 'exponential' | 'inverse' | 'linear';
export type TPanningModel = 'HRTF' | 'equalpower';
export type TOscillatorType = 'custom' | 'sawtooth' | 'sine' | 'square' | 'triangle';
export type TNativeExternal = object & {
    readonly __nativeExternal: unique symbol;
};
export type TNativeConstructor<TArgs extends readonly unknown[], TInstance extends object> = {
    prototype: TInstance;
    new (...args: TArgs): TInstance;
};
export type TNativeEs5Constructor<TArgs extends readonly unknown[], TInstance extends object> = TNativeConstructor<TArgs, TInstance> & ((...args: TArgs) => TInstance);
export type TAudioBufferData = ArrayLike<number> & object;
export type TAudioBufferOptions = Readonly<{
    length?: number;
    numberOfChannels?: number;
    sampleRate?: number;
}>;
export type TAudioContextOptions = Readonly<{
    sampleRate?: number;
}>;
export type TAudioNodeOptions = Readonly<Record<string, unknown>>;
export type TAudioObject = EventEmitter & {
    destroy: () => void;
};
export type TNativeAudioParam = TAudioObject & {
    value: number;
    readonly defaultValue: number;
    readonly maxValue: number;
    readonly minValue: number;
    cancelAndHoldAtTime: (startTime: number) => void;
    cancelScheduledValues: (startTime: number) => void;
    exponentialRampToValueAtTime: (value: number, time: number) => void;
    linearRampToValueAtTime: (value: number, time: number) => void;
    setTargetAtTime: (target: number, time: number, timeConstant: number) => void;
    setValueAtTime: (value: number, time: number) => void;
    setValueCurveAtTime: (values: readonly number[], time: number, duration: number) => void;
};
export type TAudioParam = TNativeAudioParam & {
    onended: TAudioEventCallbackList;
    onerror: TAudioEventCallbackList;
};
export type TAudioNode = TAudioObject & {
    channelCount: number;
    channelCountMode: TChannelCountMode;
    channelInterpretation: TChannelInterpretation;
    readonly context: TBaseAudioContext;
    readonly numberOfInputs: number;
    readonly numberOfOutputs: number;
    connect: (destination: TAudioNode | TAudioParam, output?: number, input?: number) => void;
    diagnose: () => void;
    disconnect: (destination?: TAudioNode | TAudioParam | number, output?: number, input?: number) => void;
    onended: TAudioEventCallbackList;
    onerror: TAudioEventCallbackList;
};
export type TAudioBuffer = TAudioObject & {
    readonly duration: number;
    readonly length: number;
    readonly numberOfChannels: number;
    readonly sampleRate: number;
    copyFromChannel: (destination: TAudioBufferData, channelNumber: number, startInChannel: number) => void;
    copyToChannel: (source: TAudioBufferData, channelNumber: number, startInChannel: number) => void;
    getChannelData: (channelIndex: number) => void;
};
export type TAudioListener = TAudioObject & {
    readonly forwardX: TAudioParam;
    readonly forwardY: TAudioParam;
    readonly forwardZ: TAudioParam;
    readonly positionX: TAudioParam;
    readonly positionY: TAudioParam;
    readonly positionZ: TAudioParam;
    readonly upX: TAudioParam;
    readonly upY: TAudioParam;
    readonly upZ: TAudioParam;
    setOrientation: (x: number, y: number, z: number, xUp: number, yUp: number, zUp: number) => void;
    setPosition: (x: number, y: number, z: number) => void;
};
export type TBaseAudioContext = TAudioObject & {
    readonly currentTime: number;
    readonly destination: TAudioDestinationNode;
    readonly listener: TAudioListener;
    readonly sampleRate: number;
    readonly state: TAudioContextState;
    decodeAudioData: (source: Buffer, cb: (buffer: TAudioBuffer) => void) => void;
    onerror: TAudioEventCallbackList;
    onstatechange: TAudioEventCallbackList;
    resume: () => void;
    update: () => void;
};
export type TAudioContext = TBaseAudioContext & {
    readonly baseLatency: number;
    close: () => void;
    getOutputTimestamp: () => void;
    suspend: () => void;
};
export type TAudioDestinationNode = TAudioNode & {
    readonly maxChannelCount: number;
};
export type TAudioScheduledSourceNode = TAudioNode & {
    start: (when?: number) => void;
    stop: (when?: number) => void;
};
export type TAnalyserNode = TAudioNode & {
    fftSize: number;
    maxDecibels: number;
    minDecibels: number;
    smoothingTimeConstant: number;
    readonly frequencyBinCount: number;
    getByteFrequencyData: (array: Uint8Array) => void;
    getByteTimeDomainData: (array: Uint8Array) => void;
    getFloatFrequencyData: (array: Float32Array) => void;
    getFloatTimeDomainData: (array: Float32Array) => void;
};
export type TBiquadFilterNode = TAudioNode & {
    type: number;
    readonly Q: TAudioParam;
    readonly detune: TAudioParam;
    readonly frequency: TAudioParam;
    readonly gain: TAudioParam;
    getFrequencyResponse: () => void;
};
export type TConvolverNode = TAudioNode & {
    buffer: TAudioBuffer;
    normalize: boolean;
};
export type TDelayNode = TAudioNode & {
    readonly delayTime: TAudioParam;
};
export type TGainNode = TAudioNode & {
    readonly gain: TAudioParam;
};
export type TPannerNode = TAudioNode & {
    coneInnerAngle: number;
    coneOuterAngle: number;
    coneOuterGain: number;
    distanceModel: TDistanceModel;
    maxDistance: number;
    panningModel: TPanningModel;
    readonly orientationX: TAudioParam;
    readonly orientationY: TAudioParam;
    readonly orientationZ: TAudioParam;
    readonly positionX: TAudioParam;
    readonly positionY: TAudioParam;
    readonly positionZ: TAudioParam;
    refDistance: number;
    rolloffFactor: number;
    setOrientation: (x: number, y: number, z: number) => void;
    setPosition: (x: number, y: number, z: number) => void;
    setVelocity: (x: number, y: number, z: number) => void;
};
export type TAudioBufferSourceNode = TAudioScheduledSourceNode & {
    buffer: TAudioBuffer;
    loop: boolean;
    loopEnd: number;
    loopStart: number;
    readonly detune: TAudioParam;
    readonly playbackRate: TAudioParam;
    start: (when?: number, grainOffset?: number, grainDuration?: number) => void;
};
export type TOscillatorNode = TAudioScheduledSourceNode & {
    type: TOscillatorType;
    readonly detune: TAudioParam;
    readonly frequency: TAudioParam;
    setPeriodicWave: (periodicWave: object) => void;
};
export type TNative = Readonly<{
    AnalyserNode: TNativeEs5Constructor<[context: TBaseAudioContext, paramCtor: TAudioParamConstructor, opts: TAudioNodeOptions], TAnalyserNode>;
    AudioBuffer: TNativeEs5Constructor<[context: TBaseAudioContext, source?: TNativeExternal | TAudioBufferOptions], TAudioBuffer>;
    AudioBufferSourceNode: TNativeEs5Constructor<[context: TBaseAudioContext, paramCtor: TAudioParamConstructor, opts: TAudioNodeOptions], TAudioBufferSourceNode>;
    AudioContext: TNativeEs5Constructor<[sampleRate?: number], TAudioContext>;
    AudioDestinationNode: TNativeEs5Constructor<[context: TBaseAudioContext, node: TNativeExternal], TAudioDestinationNode>;
    AudioListener: TNativeEs5Constructor<[context: TBaseAudioContext, listener: TNativeExternal, paramCtor: TAudioParamConstructor], TAudioListener>;
    AudioNode: TNativeEs5Constructor<[context: TBaseAudioContext, node: TNativeExternal], TAudioNode>;
    AudioParam: TAudioParamConstructor;
    AudioScheduledSourceNode: TNativeEs5Constructor<[context: TBaseAudioContext, node: TNativeExternal], TAudioScheduledSourceNode>;
    BaseAudioContext: TNativeEs5Constructor<[context: TNativeExternal, sampleRate: number], TBaseAudioContext> & {
        hrtf: string;
    };
    BiquadFilterNode: TNativeEs5Constructor<[context: TBaseAudioContext, paramCtor: TAudioParamConstructor, opts: TAudioNodeOptions], TBiquadFilterNode>;
    ConvolverNode: TNativeEs5Constructor<[context: TBaseAudioContext, paramCtor: TAudioParamConstructor, opts: TAudioNodeOptions], TConvolverNode>;
    DelayNode: TNativeEs5Constructor<[context: TBaseAudioContext, paramCtor: TAudioParamConstructor, opts: TAudioNodeOptions], TDelayNode>;
    GainNode: TNativeEs5Constructor<[context: TBaseAudioContext, paramCtor: TAudioParamConstructor, opts: TAudioNodeOptions], TGainNode>;
    OscillatorNode: TNativeEs5Constructor<[context: TBaseAudioContext, paramCtor: TAudioParamConstructor, opts: TAudioNodeOptions], TOscillatorNode>;
    PannerNode: TNativeEs5Constructor<[context: TBaseAudioContext, paramCtor: TAudioParamConstructor, opts: TAudioNodeOptions], TPannerNode>;
}>;
export type TAudioParamConstructor = TNativeConstructor<[context: TBaseAudioContext, param: TNativeExternal], TNativeAudioParam>;
export declare const native: TNative;
