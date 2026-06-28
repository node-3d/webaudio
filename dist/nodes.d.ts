import type { TAnalyserNode, TAudioBufferSourceNode, TAudioNode, TAudioNodeOptions, TAudioScheduledSourceNode, TBaseAudioContext, TBiquadFilterNode, TConvolverNode, TDelayNode, TGainNode, TOscillatorNode, TPannerNode } from './native.ts';
type TNodeConstructor<TInstance extends object = TAudioNode> = new (ctx: TBaseAudioContext, opts?: TAudioNodeOptions) => TInstance;
type TExportedNodeName = 'AnalyserNode' | 'AudioBufferSourceNode' | 'AudioScheduledSourceNode' | 'BiquadFilterNode' | 'ConvolverNode' | 'DelayNode' | 'GainNode' | 'OscillatorNode' | 'PannerNode';
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
declare const nodes: TNodeMap;
declare const AudioScheduledSourceNode: TNodeConstructor<TAudioScheduledSourceNode> & TNodeConstructor<TAudioNode>, AnalyserNode: TNodeConstructor<TAnalyserNode> & TNodeConstructor<TAudioNode>, BiquadFilterNode: TNodeConstructor<TBiquadFilterNode> & TNodeConstructor<TAudioNode>, ConvolverNode: TNodeConstructor<TConvolverNode> & TNodeConstructor<TAudioNode>, DelayNode: TNodeConstructor<TDelayNode> & TNodeConstructor<TAudioNode>, GainNode: TNodeConstructor<TGainNode> & TNodeConstructor<TAudioNode>, PannerNode: TNodeConstructor<TPannerNode> & TNodeConstructor<TAudioNode>, AudioBufferSourceNode: TNodeConstructor<TAudioBufferSourceNode> & TNodeConstructor<TAudioNode>, OscillatorNode: TNodeConstructor<TOscillatorNode> & TNodeConstructor<TAudioNode>;
export { AudioScheduledSourceNode, AnalyserNode, BiquadFilterNode, ConvolverNode, DelayNode, GainNode, PannerNode, AudioBufferSourceNode, OscillatorNode, };
export { nodes };
