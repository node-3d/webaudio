import { readFile } from 'node:fs/promises';
import { AudioContext } from '@node-3d/webaudio';
import type { TAudioBuffer } from '@node-3d/webaudio';

const context = new AudioContext();

const clip = await readFile(`${import.meta.dirname}/samples/hit.wav`);

const musicClip = await new Promise<TAudioBuffer>((res) => {
	context.decodeAudioData(clip, (b) => res(b));
});

const gain = context.createGain();
gain.gain.value = 0.0625;

const musicClipNode = context.createBufferSource();

musicClipNode.buffer = musicClip;
musicClipNode.connect(gain);

gain.connect(context.destination);

let isActive = false;
let i = 1;

musicClipNode.on('ended', () => {
	isActive = false;
});
musicClipNode.on('ended', () => console.log('Played:', i++));

setInterval(() => {
	if (isActive) {
		console.log('STILL ACTIVE!');
	}
	isActive = true;
	musicClipNode.start(0);
}, 200).unref();

// 10 sec
await new Promise((res) => {
	setTimeout(res, 5000);
});

console.log('DONE');
