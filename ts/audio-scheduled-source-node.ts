import { inspect, inherits } from 'node:util';
import { AudioNode } from './audio-node.ts';
import { native } from './native.ts';
import type {
	TAudioScheduledSourceNode,
	TBaseAudioContext,
	TNativeConstructor,
	TNativeExternal,
} from './native.ts';

const { AudioScheduledSourceNode } = native;

inherits(AudioScheduledSourceNode, AudioNode);

type TAudioScheduledSourceNodeConstructor =
	TNativeConstructor<[ctx: TBaseAudioContext, node: TNativeExternal], TAudioScheduledSourceNode>;

const JsAudioScheduledSourceNode = function JsAudioScheduledSourceNode(
	this: TAudioScheduledSourceNode,
	ctx: TBaseAudioContext,
	node: TNativeExternal,
): void {
	AudioScheduledSourceNode.call(this, ctx, node);
} as unknown as TAudioScheduledSourceNodeConstructor;

JsAudioScheduledSourceNode.prototype = {
	
	[inspect.custom](): string { return this.toString(); },
	
	toString(): string {
		return 'AudioScheduledSourceNode {}';
	},
	
} as unknown as TAudioScheduledSourceNode;

inherits(JsAudioScheduledSourceNode, AudioScheduledSourceNode);

export { JsAudioScheduledSourceNode as AudioScheduledSourceNode };
