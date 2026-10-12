import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { describe, it } from 'node:test';
import { AudioBuffer, AudioContext } from '@node-3d/webaudio';
import type { TAudioBuffer } from '@node-3d/webaudio';

describe('AudioBuffer', () => {
	it('creates zero-filled buffers with the specified dimensions', () => {
		const context = new AudioContext();
		const buffer = context.createBuffer(2, 8, 48_000);
		assert.equal(buffer.numberOfChannels, 2);
		assert.equal(buffer.length, 8);
		assert.equal(buffer.sampleRate, 48_000);
		assert.equal(buffer.duration, 8 / 48_000);
		assert.deepEqual(
			[...buffer.getChannelData(0)],
			Array.from({ length: 8 }, () => 0),
		);
		assert.equal(buffer.getChannelData(0), buffer.getChannelData(0));
		assert.equal(new AudioBuffer({ length: 4, sampleRate: 3000 }).numberOfChannels, 1);
		assert.equal(context.createBuffer(32, 1, 768_000).numberOfChannels, 32);
	});

	it('exposes writable channels and copies partial ranges', () => {
		const buffer = new AudioBuffer({ numberOfChannels: 2, length: 4, sampleRate: 48_000 });
		const left = buffer.getChannelData(0);
		left[0] = 0.25;
		buffer.copyToChannel(new Float32Array([0.5, 0.75, 1]), 0, 2);
		assert.deepEqual([...left], [0.25, 0, 0.5, 0.75]);
		const destination = new Float32Array([9, 9, 9]);
		buffer.copyFromChannel(destination, 0, 3);
		assert.deepEqual([...destination], [0.75, 9, 9]);
		buffer.copyToChannel(left.subarray(0, 3), 0, 1);
		assert.deepEqual([...left], [0.25, 0.25, 0, 0.5]);
		assert.deepEqual([...buffer.getChannelData(1)], [0, 0, 0, 0]);
		structuredClone(left.buffer, { transfer: [left.buffer] });
		assert.equal(buffer.getChannelData(0).length, 4);
	});

	it('rejects missing and out-of-range inputs without terminating Node', () => {
		const context = new AudioContext();
		assert.throws(() => Reflect.apply(context.createBuffer, context, []), TypeError);
		assert.throws(() => Reflect.construct(AudioBuffer, []), TypeError);
		assert.throws(() => context.createBuffer(0, 4, 48_000), { name: 'NotSupportedError' });
		assert.throws(() => context.createBuffer(1, 0, 48_000), { name: 'NotSupportedError' });
		assert.throws(() => context.createBuffer(1, 4, 2999), { name: 'NotSupportedError' });
		assert.throws(() => context.createBuffer(1, 4, 768_001), { name: 'NotSupportedError' });
		const buffer = context.createBuffer(1, 4, 48_000);
		assert.throws(() => buffer.getChannelData(1), { name: 'IndexSizeError' });
		assert.throws(() => buffer.copyToChannel(new Float32Array(1), 1), {
			name: 'IndexSizeError',
		});
		const source = context.createBufferSource();
		assert.throws(() => Reflect.set(source, 'buffer', {}), TypeError);
	});

	it('keeps decoded buffers and source playback usable', async () => {
		const context = new AudioContext();
		const wav = readFileSync(new URL('../examples/samples/hit.wav', import.meta.url));
		const decoded = await new Promise<TAudioBuffer>((res) => {
			context.decodeAudioData(wav, res);
		});
		assert.ok(decoded.length > 0);
		assert.ok(decoded.sampleRate > 0);
		assert.equal(decoded.getChannelData(0).length, decoded.length);
		const generated = context.createBuffer(1, 8, context.sampleRate);
		const channel = generated.getChannelData(0);
		channel[0] = 0.5;
		const source = context.createBufferSource();
		source.buffer = generated;
		assert.equal(channel.length, 8);
		source.connect(context.destination);
		source.start();
		assert.equal(channel.length, 0);
		assert.equal(generated.getChannelData(0)[0], 0.5);
	});
});
