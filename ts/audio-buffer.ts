import { inspect, inherits } from 'node:util';
import Emitter from 'node:events';
import { native } from './native.ts';

const { AudioBuffer } = native;

inherits(AudioBuffer, Emitter);

class JsAudioBuffer extends AudioBuffer {
	public [inspect.custom](): string {
		return this.toString();
	}

	public toString(): string {
		return 'AudioBuffer {}';
	}
}

export { JsAudioBuffer as AudioBuffer };
