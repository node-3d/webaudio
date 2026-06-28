import type { TAudioDestinationNode, TBaseAudioContext, TNativeConstructor, TNativeExternal } from './native.ts';
type TAudioDestinationNodeConstructor = TNativeConstructor<[ctx: TBaseAudioContext, node: TNativeExternal], TAudioDestinationNode>;
declare const JsAudioDestinationNode: TAudioDestinationNodeConstructor;
export { JsAudioDestinationNode as AudioDestinationNode };
