import { inspect, inherits } from 'node:util';
import { AudioNode } from './audio-node.ts';
import { native } from './native.ts';
import type {
	TAudioDestinationNode,
	TBaseAudioContext,
	TNativeConstructor,
	TNativeExternal,
} from './native.ts';

const { AudioDestinationNode } = native;

inherits(AudioDestinationNode, AudioNode);

type TAudioDestinationNodeConstructor =
	TNativeConstructor<[ctx: TBaseAudioContext, node: TNativeExternal], TAudioDestinationNode>;

const JsAudioDestinationNode = function JsAudioDestinationNode(
	this: TAudioDestinationNode,
	ctx: TBaseAudioContext,
	node: TNativeExternal,
): void {
	AudioDestinationNode.call(this, ctx, node);
} as unknown as TAudioDestinationNodeConstructor;

JsAudioDestinationNode.prototype = {
	
	[inspect.custom](): string { return this.toString(); },
	
	toString(): string {
		return 'AudioDestinationNode {}';
	},
	
} as unknown as TAudioDestinationNode;

inherits(JsAudioDestinationNode, AudioDestinationNode);

export { JsAudioDestinationNode as AudioDestinationNode };
