import { inspect, inherits } from 'node:util';
import Emitter from 'node:events';
import { setEventCallbacks } from './events.ts';
import { native } from './native.ts';
import type {
	TAudioEventCallback,
	TAudioEventCallbackList,
	TAudioNode,
	TBaseAudioContext,
	TNativeConstructor,
	TNativeExternal,
} from './native.ts';

const { AudioNode } = native;

inherits(AudioNode, Emitter);

const nonGcRefs = new Set<TAudioNode>();

type TAudioNodeConstructor =
	TNativeConstructor<[ctx: TBaseAudioContext, node: TNativeExternal], TAudioNode>;

const JsAudioNode = function JsAudioNode(
	this: TAudioNode,
	ctx: TBaseAudioContext,
	node: TNativeExternal,
): void {
	AudioNode.call(this, ctx, node);
	
	// Prevent garbage collection until node is intentionally destroyed
	nonGcRefs.add(this);
	this.on('destroy', () => {
		nonGcRefs.delete(this);
	});
} as unknown as TAudioNodeConstructor;

const audioNodePrototype: Partial<TAudioNode> & ThisType<TAudioNode> & {
	[inspect.custom](): string;
	toString(): string;
} = {
	get onerror(): TAudioEventCallbackList { return this.listeners('error') as TAudioEventCallback[]; },
	set onerror(cb: TAudioEventCallbackList) {
		setEventCallbacks(this, 'error', cb);
	},
	
	get onended(): TAudioEventCallbackList { return this.listeners('ended') as TAudioEventCallback[]; },
	set onended(cb: TAudioEventCallbackList) {
		setEventCallbacks(this, 'ended', cb);
	},
	
	[inspect.custom](): string { return this.toString(); },
	
	toString(): string {
		return 'AudioNode {}';
	},
};

JsAudioNode.prototype = audioNodePrototype as TAudioNode;

inherits(JsAudioNode, AudioNode);

export { JsAudioNode as AudioNode };
