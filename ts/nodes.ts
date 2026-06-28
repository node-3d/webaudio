import { inspect, inherits } from 'node:util';
import { AudioNode } from './audio-node.ts';
import { AudioParam } from './audio-param.ts';
import { AudioScheduledSourceNode as BaseAudioScheduledSourceNode } from './audio-scheduled-source-node.ts';
import { native } from './native.ts';
import type {
	TAnalyserNode,
	TAudioBufferSourceNode,
	TAudioNode,
	TAudioNodeOptions,
	TAudioScheduledSourceNode,
	TBaseAudioContext,
	TBiquadFilterNode,
	TConvolverNode,
	TDelayNode,
	TGainNode,
	TNativeConstructor,
	TOscillatorNode,
	TPannerNode,
} from './native.ts';

const baseDescs = [
	'AnalyserNode',
	'BiquadFilterNode',
	// 'ChannelMergerNode',
	// 'ChannelSplitterNode',
	'ConvolverNode',
	'DelayNode',
	// 'DynamicsCompressorNode',
	'GainNode',
	// 'IIRFilterNode',
	'PannerNode',
	// 'PeriodicWaveNode',
	// 'ScriptProcessorNode',
	// 'StereoPannerNode',
	// 'WaveShaperNode',
] as const;

const scheduledDescs = [
	'AudioBufferSourceNode', 'OscillatorNode',
] as const;

type TNodeConstructor<TInstance extends object = TAudioNode> =
	new (ctx: TBaseAudioContext, opts?: TAudioNodeOptions) => TInstance;
type TNativeNodeConstructor =
	TNativeConstructor<[ctx: TBaseAudioContext, paramCtor: typeof AudioParam, opts: TAudioNodeOptions], object>;

type TInheritsConstructor = object;
type TExportedNodeName =
	| 'AnalyserNode'
	| 'AudioBufferSourceNode'
	| 'AudioScheduledSourceNode'
	| 'BiquadFilterNode'
	| 'ConvolverNode'
	| 'DelayNode'
	| 'GainNode'
	| 'OscillatorNode'
	| 'PannerNode';
type TNodeMap = {
	AnalyserNode: TNodeConstructor<TAnalyserNode>;
	AudioBufferSourceNode: TNodeConstructor<TAudioBufferSourceNode>;
	AudioScheduledSourceNode: TNodeConstructor<TAudioScheduledSourceNode>;
	BiquadFilterNode: TNodeConstructor<TBiquadFilterNode>;
	ConvolverNode: TNodeConstructor<TConvolverNode>;
	DelayNode: TNodeConstructor<TDelayNode>;
	GainNode: TNodeConstructor<TGainNode>;
	OscillatorNode: TNodeConstructor<TOscillatorNode>;
	PannerNode: TNodeConstructor<TPannerNode>;
} & Record<TExportedNodeName, TNodeConstructor> & Record<string, TNodeConstructor>;

const subclassBase = (name: keyof typeof native, SuperNode: TInheritsConstructor): TNodeConstructor => {
	const SuperClass = native[name] as TNativeNodeConstructor;
	inherits(SuperClass, SuperNode as typeof Object);
	
	class JsNode extends SuperClass {
		private readonly _opts: TAudioNodeOptions;
		
		public constructor(ctx: TBaseAudioContext, opts: TAudioNodeOptions = {}) {
			super(ctx, AudioParam, opts);
			this._opts = opts;
		}
		
		public [inspect.custom](): string { return this.toString(); }
		
		public toString(): string {
			return `${name} ${JSON.stringify(this._opts, null, '\t')}`;
		}
	}
	
	return JsNode as unknown as TNodeConstructor;
};

const baseNodes: Record<string, TNodeConstructor> = {
	AudioScheduledSourceNode: BaseAudioScheduledSourceNode as unknown as TNodeConstructor,
};

for (const name of baseDescs) {
	baseNodes[name] = subclassBase(name, AudioNode);
}

const scheduledNodes: Record<string, TNodeConstructor> = {};

for (const name of scheduledDescs) {
	scheduledNodes[name] = subclassBase(name, BaseAudioScheduledSourceNode);
}

const nodes = {
	...baseNodes,
	...scheduledNodes,
} as unknown as TNodeMap;

const {
	AudioScheduledSourceNode,
	AnalyserNode,
	BiquadFilterNode,
	ConvolverNode,
	DelayNode,
	GainNode,
	PannerNode,
	AudioBufferSourceNode,
	OscillatorNode,
} = nodes;

export {
	AudioScheduledSourceNode,
	AnalyserNode,
	BiquadFilterNode,
	ConvolverNode,
	DelayNode,
	GainNode,
	PannerNode,
	AudioBufferSourceNode,
	OscillatorNode,
};

export { nodes };
