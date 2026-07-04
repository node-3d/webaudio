import { readFile } from 'node:fs/promises';
import { AudioContext } from '@node-3d/webaudio';
import type { TAudioBuffer } from '@node-3d/webaudio';

const context = new AudioContext();

const clip = await readFile(`${import.meta.dirname}/samples/trainrolling.wav`);

const musicClip = await new Promise<TAudioBuffer>((res) => {
	context.decodeAudioData(clip, (b) => res(b));
});

const oscillator = context.createOscillator();

const gain = context.createGain();
gain.gain.value = 0.0625;

const musicClipNode = context.createBufferSource();

musicClipNode.on('ended', () => {
	console.log('.on("ended"): Track "trainrolling.wav" ended.');
});
musicClipNode.on('ended', () => {
	console.log('.onended: Track "trainrolling.wav" ended.');
});

// musicClipNode.on('ended', () => { setTimeout(() => musicClipNode.start(0), 100); });

musicClipNode.buffer = musicClip;

musicClipNode.connect(gain);

musicClipNode.start(0);

// osc -> gain -> destination
oscillator.connect(gain);

gain.connect(context.destination);

oscillator.frequency.value = 440;

oscillator.type = 'sine';

oscillator.start(0);

// 6 sec
await new Promise((res) => {
	setTimeout(res, 6000);
});

console.log('DONE');
