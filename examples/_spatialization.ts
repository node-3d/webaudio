import { readFile } from 'node:fs/promises';
import { AudioContext } from '@node-3d/webaudio';
import type { TAudioBuffer } from '@node-3d/webaudio';

const context = new AudioContext();

const voice = await readFile(`${import.meta.dirname}/samples/voice.ogg`);

const audioClip = await new Promise<TAudioBuffer>((res) => {
	context.decodeAudioData(voice, (b) => res(b));
});
const audioClipNode = context.createBufferSource();
audioClipNode.buffer = audioClip;

const panner = context.createPanner();
// panner.panningModel = 'HRTF';
panner.connect(context.destination);

audioClipNode.connect(panner);
audioClipNode.start(0);
audioClipNode.loop = true;

context.listener.setPosition(0, 0, 0);

for (let i = 0; i < 1000; i++) {
	const rad = Math.PI * i * 0.001;
	const r = 11 - i / 1000;
	const s = r * Math.sin(rad);
	const c = r * Math.cos(rad);

	panner.setVelocity(-s, 0, c); // derivative
	// panner.setPosition(c, 0, s);
	panner.positionX.value = c;
	panner.positionZ.value = s;

	// Wait
	// oxlint-disable-next-line no-await-in-loop
	await new Promise((res) => {
		setTimeout(res, 15);
	});
}

// for (let i = 0; i < 1000; i++) {

// 	const rad = Math.PI * i * 0.001;
// 	const r = 11 - i / 1000;
// 	const s = r * Math.sin(rad);
// 	const c = r * Math.cos(rad);

// 	panner.setVelocity(-s, 0, c); // derivative
// 	panner.setPosition(c, 0, s);

// 	// Wait
// 	await new Promise(res => setTimeout(res, 15));

// }

console.log('DONE');
