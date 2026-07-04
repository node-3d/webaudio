import { inspect, inherits } from 'node:util';
import Emitter from 'node:events';
import { setEventCallbacks } from './events.ts';
import { native } from './native.ts';
import type { TAudioEventCallback, TAudioEventCallbackList } from './native.ts';

const { AudioParam } = native;

inherits(AudioParam, Emitter);

class JsAudioParam extends AudioParam {
	public get onerror(): TAudioEventCallbackList {
		return this.listeners('error') as TAudioEventCallback[];
	}
	public set onerror(cb: TAudioEventCallbackList) {
		setEventCallbacks(this, 'error', cb);
	}

	public get onended(): TAudioEventCallbackList {
		return this.listeners('ended') as TAudioEventCallback[];
	}
	public set onended(cb: TAudioEventCallbackList) {
		setEventCallbacks(this, 'ended', cb);
	}

	public [inspect.custom](): string {
		return this.toString();
	}

	public toString(): string {
		return `AudioParam { ${this.value} }`;
	}
}

export { JsAudioParam as AudioParam };
