import type { TAudioNode, TBaseAudioContext, TNativeConstructor, TNativeExternal } from './native.ts';
type TAudioNodeConstructor = TNativeConstructor<[ctx: TBaseAudioContext, node: TNativeExternal], TAudioNode>;
declare const JsAudioNode: TAudioNodeConstructor;
export { JsAudioNode as AudioNode };
