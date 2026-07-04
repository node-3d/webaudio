import { readFile } from 'node:fs/promises';
import { AudioContext } from '@node-3d/webaudio';
import type { TAudioBuffer } from '@node-3d/webaudio';

const context = new AudioContext();

const cello = await readFile(`${import.meta.dirname}/samples/voice.ogg`);

const audioClip = await new Promise<TAudioBuffer>((res) => {
	context.decodeAudioData(cello, (b) => res(b));
});
const audioClipNode = context.createBufferSource();
audioClipNode.buffer = audioClip;

const pingping = context.createDelay(3);

pingping.delayTime.value = 3;
pingping.connect(context.destination);

audioClipNode.connect(pingping);
audioClipNode.start(0);

// 20 sec
await new Promise((res) => {
	setTimeout(res, 20000);
});

console.log('DONE');
