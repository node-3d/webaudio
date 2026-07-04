import assert from 'node:assert/strict';
import { describe, it } from 'node:test';
import { AudioContext } from '@node-3d/webaudio';

describe('WebAudio', () => {
	const context = new AudioContext();

	it('creates an AudioContext instance', () => {
		assert.ok(context instanceof AudioContext);
	});

	it('creates an OscillatorNode instance', () => {
		const oscillator = context.createOscillator();
		assert.strictEqual(typeof oscillator, 'object');
	});
});
