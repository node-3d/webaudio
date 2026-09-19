// oxlint-disable typescript/method-signature-style
import { inspect, inherits } from 'node:util';
import { hrtf } from '@node-3d/deps-labsound';
import Emitter from 'node:events';
import { AudioDestinationNode } from './audio-destination-node.ts';
import { AudioBuffer } from './audio-buffer.ts';
import { AudioListener } from './audio-listener.ts';
import { setEventCallbacks } from './events.ts';
import { nodes } from './nodes.ts';
import { native } from './native.ts';
import type {
	TAnalyserNode,
	TAudioBuffer,
	TAudioBufferSourceNode,
	TAudioEventCallback,
	TAudioEventCallbackList,
	TAudioNodeOptions,
	TBaseAudioContext,
	TBiquadFilterNode,
	TConvolverNode,
	TDelayNode,
	TGainNode,
	TNativeConstructor,
	TNativeExternal,
	TOscillatorNode,
	TPannerNode,
} from './native.ts';

type TNativeBaseAudioContext = TBaseAudioContext & {
	_initListener: TJsBaseAudioContext['_initListener'];
	decodeAudioData: (
		source: Buffer,
		cb: (buffer: TAudioBuffer) => void,
		bufferCtor: typeof AudioBuffer,
	) => void;
};

type TNativeBaseAudioContextConstructor = TNativeConstructor<
	[ctx: TNativeExternal, sampleRate?: number],
	TNativeBaseAudioContext
> & {
	hrtf: string;
};

const BaseAudioContext = native.BaseAudioContext as unknown as TNativeBaseAudioContextConstructor;

inherits(BaseAudioContext, Emitter);
BaseAudioContext.hrtf = hrtf;

export type TJsBaseAudioContext = TBaseAudioContext & {
	_initListener: (
		destinationCtor: typeof AudioDestinationNode,
		listenerCtor: typeof AudioListener,
		sampleRate: number,
	) => void;
	createAnalyser: (opts?: TAudioNodeOptions) => TAnalyserNode;
	createBiquadFilter: (opts?: TAudioNodeOptions) => TBiquadFilterNode;
	createBuffer: (opts?: TAudioNodeOptions) => TAudioBuffer;
	createBufferSource: (opts?: TAudioNodeOptions) => TAudioBufferSourceNode;
	createConvolver: (opts?: TAudioNodeOptions) => TConvolverNode;
	createDelay: (maxDelayTime?: number) => TDelayNode;
	createGain: (opts?: TAudioNodeOptions) => TGainNode;
	createOscillator: (opts?: TAudioNodeOptions) => TOscillatorNode;
	createPanner: (opts?: TAudioNodeOptions) => TPannerNode;
	createChannelMerger: (opts?: TAudioNodeOptions) => object;
	createChannelSplitter: (opts?: TAudioNodeOptions) => object;
	createConstantSource: (opts?: TAudioNodeOptions) => object;
	createDynamicsCompressor: (opts?: TAudioNodeOptions) => object;
	createIIRFilter: (opts?: TAudioNodeOptions) => object;
	createPeriodicWave: (opts?: TAudioNodeOptions) => object;
	createScriptProcessor: (opts?: TAudioNodeOptions) => object;
	createStereoPanner: (opts?: TAudioNodeOptions) => object;
	createWaveShaper: (opts?: TAudioNodeOptions) => object;
};

type TBaseAudioContextConstructor = TNativeConstructor<
	[ctx: TNativeExternal, sampleRate?: number],
	TJsBaseAudioContext
>;

const JsBaseAudioContext = function JsBaseAudioContext(
	this: TJsBaseAudioContext,
	ctx: TNativeExternal,
	sampleRate = -1,
): void {
	BaseAudioContext.call(this, ctx, sampleRate);
	this._initListener(AudioDestinationNode, AudioListener, sampleRate);
} as unknown as TBaseAudioContextConstructor;

const baseAudioContextPrototype: Partial<TJsBaseAudioContext> &
	ThisType<TJsBaseAudioContext> & {
		[inspect.custom](): string;
		toString(): string;
	} = {
	get onerror(): TAudioEventCallbackList {
		return this.listeners('error') as TAudioEventCallback[];
	},
	set onerror(cb: TAudioEventCallbackList) {
		setEventCallbacks(this, 'error', cb);
	},

	get onstatechange(): TAudioEventCallbackList {
		return this.listeners('statechange') as TAudioEventCallback[];
	},
	set onstatechange(cb: TAudioEventCallbackList) {
		setEventCallbacks(this, 'statechange', cb);
	},

	[inspect.custom](): string {
		// oxlint-disable-next-line typescript/no-base-to-string
		return this.toString();
	},

	toString(): string {
		return 'BaseAudioContext {}';
	},

	decodeAudioData(audioData: Buffer, successCallback: (buffer: TAudioBuffer) => void): void {
		BaseAudioContext.prototype.decodeAudioData.call(
			this,
			audioData,
			successCallback,
			AudioBuffer,
		);
	},

	createAnalyser(opts: TAudioNodeOptions = {}) {
		return new nodes.AnalyserNode(this, opts);
	},

	createBiquadFilter(opts: TAudioNodeOptions = {}) {
		return new nodes.BiquadFilterNode(this, opts);
	},

	createBuffer(opts: TAudioNodeOptions = {}) {
		return new AudioBuffer(this, opts);
	},

	createBufferSource(opts: TAudioNodeOptions = {}) {
		return new nodes.AudioBufferSourceNode(this, opts);
	},

	createChannelMerger() {
		throw new Error('createChannelMerger is not implemented by this audio backend');
	},

	createChannelSplitter() {
		throw new Error('createChannelSplitter is not implemented by this audio backend');
	},

	createConstantSource() {
		throw new Error('createConstantSource is not implemented by this audio backend');
	},

	createConvolver(opts: TAudioNodeOptions = {}) {
		return new nodes.ConvolverNode(this, opts);
	},

	createDelay(maxDelayTime = 1) {
		return new nodes.DelayNode(this, { maxDelayTime });
	},

	createDynamicsCompressor() {
		throw new Error('createDynamicsCompressor is not implemented by this audio backend');
	},

	createGain(opts: TAudioNodeOptions = {}) {
		return new nodes.GainNode(this, opts);
	},

	createIIRFilter() {
		throw new Error('createIIRFilter is not implemented by this audio backend');
	},

	createOscillator(opts: TAudioNodeOptions = {}) {
		return new nodes.OscillatorNode(this, opts);
	},

	createPanner(opts: TAudioNodeOptions = {}) {
		return new nodes.PannerNode(this, opts);
	},

	createPeriodicWave() {
		throw new Error('createPeriodicWave is not implemented by this audio backend');
	},

	createScriptProcessor() {
		throw new Error('createScriptProcessor is not implemented by this audio backend');
	},

	createStereoPanner() {
		throw new Error('createStereoPanner is not implemented by this audio backend');
	},

	createWaveShaper() {
		throw new Error('createWaveShaper is not implemented by this audio backend');
	},
};

inherits(JsBaseAudioContext, BaseAudioContext);
Object.defineProperties(
	JsBaseAudioContext.prototype,
	Object.getOwnPropertyDescriptors(baseAudioContextPrototype),
);

export { JsBaseAudioContext as BaseAudioContext };
