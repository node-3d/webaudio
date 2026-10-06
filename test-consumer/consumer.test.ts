import assert from 'node:assert/strict';
import test from 'node:test';
import { AudioContext } from '@node-3d/webaudio';

test('loads the packed audio addon', () => {
	assert.equal(typeof AudioContext, 'function');
	assert.equal(typeof AudioContext.prototype.createOscillator, 'function');
});
