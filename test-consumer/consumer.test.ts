import assert from 'node:assert/strict';
import test from 'node:test';
import { AudioBuffer, AudioContext } from '@node-3d/webaudio';

test('loads the packed audio addon', () => {
	assert.equal(typeof AudioContext, 'function');
	assert.equal(typeof AudioContext.prototype.createOscillator, 'function');
});

test('uses the candidate AudioBuffer implementation', () => {
	const buffer = new AudioBuffer({ length: 4, sampleRate: 48_000 });
	assert.equal(buffer.numberOfChannels, 1);
	assert.equal(buffer.length, 4);
	assert.equal(buffer.sampleRate, 48_000);
	const channel = buffer.getChannelData(0);
	assert.deepEqual([...channel], [0, 0, 0, 0]);
	channel[0] = 0.5;
	const copied = new Float32Array(1);
	buffer.copyFromChannel(copied, 0);
	assert.equal(copied[0], 0.5);
});
