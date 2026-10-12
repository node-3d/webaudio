import { inspect, inherits } from 'node:util';
import Emitter from 'node:events';
import { native } from './native.ts';
import type { TAudioBufferOptions, TBaseAudioContext, TNativeExternal } from './native.ts';

const { AudioBuffer } = native;

inherits(AudioBuffer, Emitter);

class JsAudioBuffer extends AudioBuffer {
	public constructor(options: TAudioBufferOptions);
	public constructor(options: TAudioBufferOptions | TBaseAudioContext, source?: TNativeExternal) {
		if ('length' in options) {
			super(options);
		} else {
			if (source === undefined) {
				throw new TypeError('AudioBuffer requires an options object');
			}
			// The second form is reserved for the native decoder callback.
			super(options, source);
		}
	}

	public [inspect.custom](): string {
		return this.toString();
	}

	public override toString(): string {
		return 'AudioBuffer {}';
	}
}

export { JsAudioBuffer as AudioBuffer };
