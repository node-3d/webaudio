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

	it('reports unsupported node constructors explicitly', () => {
		const unsupportedConstructors = {
			createChannelMerger: () => context.createChannelMerger(),
			createChannelSplitter: () => context.createChannelSplitter(),
			createConstantSource: () => context.createConstantSource(),
			createDynamicsCompressor: () => context.createDynamicsCompressor(),
			createIIRFilter: () => context.createIIRFilter(),
			createPeriodicWave: () => context.createPeriodicWave(),
			createScriptProcessor: () => context.createScriptProcessor(),
			createStereoPanner: () => context.createStereoPanner(),
			createWaveShaper: () => context.createWaveShaper(),
		};

		for (const [method, create] of Object.entries(unsupportedConstructors)) {
			assert.throws(create, new Error(`${method} is not implemented by this audio backend`));
		}
	});
});
