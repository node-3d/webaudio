import { inspect, inherits } from 'node:util';
import { BaseAudioContext } from './base-audio-context.ts';
import { native } from './native.ts';
import type { TJsBaseAudioContext } from './base-audio-context.ts';
import type { TAudioContext, TAudioContextOptions, TNativeConstructor } from './native.ts';

const { AudioContext } = native;

inherits(AudioContext, BaseAudioContext);

class JsAudioContext extends AudioContext {
	public constructor(opts: TAudioContextOptions = {}) {
		if (opts.sampleRate === undefined) {
			super();
		} else {
			super(opts.sampleRate);
		}
	}

	public [inspect.custom](): string {
		return this.toString();
	}

	public toString(): string {
		return 'AudioContext {}';
	}
}

const WrappedAudioContext = JsAudioContext as unknown as TNativeConstructor<
	[opts?: TAudioContextOptions],
	TAudioContext & TJsBaseAudioContext
>;

export { WrappedAudioContext as AudioContext };
