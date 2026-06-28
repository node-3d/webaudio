import type { TAudioScheduledSourceNode, TBaseAudioContext, TNativeConstructor, TNativeExternal } from './native.ts';
type TAudioScheduledSourceNodeConstructor = TNativeConstructor<[ctx: TBaseAudioContext, node: TNativeExternal], TAudioScheduledSourceNode>;
declare const JsAudioScheduledSourceNode: TAudioScheduledSourceNodeConstructor;
export { JsAudioScheduledSourceNode as AudioScheduledSourceNode };
