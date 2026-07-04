import { inspect, inherits } from 'node:util';
import Emitter from 'node:events';
import { AudioParam } from './audio-param.ts';
import { native } from './native.ts';
import type { TBaseAudioContext, TNativeExternal } from './native.ts';

const { AudioListener } = native;

inherits(AudioListener, Emitter);

class JsAudioListener extends AudioListener {
	public constructor(ctx: TBaseAudioContext, listener: TNativeExternal) {
		super(ctx, listener, AudioParam);
	}

	public [inspect.custom](): string {
		return this.toString();
	}

	public toString(): string {
		return 'AudioListener {}';
	}
}

export { JsAudioListener as AudioListener };
