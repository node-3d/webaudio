import { readFile } from 'node:fs/promises';
import { AudioContext } from '@node-3d/webaudio';
import type { TAudioBuffer, TAudioBufferSourceNode, TPannerNode } from '@node-3d/webaudio';

let total = 0;
let num = 0;

const count = 6;
type TAudioObject = {
	isPlaying: boolean;
	panner: TPannerNode;
	play: () => void;
	playbackRate: number;
	source?: TAudioBufferSourceNode;
	startTime: number;
};
type TBall = {
	audio: TAudioObject;
	down?: boolean;
	y: number;
};

const playUnavailable = (): void => {
	throw new Error('Audio play was not initialized.');
};

const objects: TBall[] = [];
const scene: TBall[] = [];

const speed = 0.002;
const height = 3;
const offset = 0.5;

const context = new AudioContext();

const clip = await readFile(`${import.meta.dirname}/samples/hit.wav`);

const buffer = await new Promise<TAudioBuffer>((res) => {
	context.decodeAudioData(clip, (b) => res(b));
});

// Create objects when audio buffer is loaded
for (let i = 0; i < count; i++) {
	const audio: TAudioObject = {
		isPlaying: false,
		panner: context.createPanner(),
		play: playUnavailable,
		playbackRate: 1,
		startTime: 0,
	};
	const ball: TBall = { audio, y: 0 };
	audio.panner.on('ended', () => {
		console.log('-PAN');
	});
	audio.panner.connect(context.destination);
	// oxlint-disable-next-line no-loop-func
	audio.play = () => {
		if (audio.isPlaying === true) {
			console.warn('Audio is already playing.');
			return;
		}
		audio.isPlaying = true;

		total++;
		console.log(total, Date.now(), '+ABSN:', ++num);

		const source = context.createBufferSource();
		source.on('ended', () => {
			audio.isPlaying = false;
			console.log(total, Date.now(), '-ABSN:', --num);
		});

		audio.source = source;
		audio.source.connect(audio.panner);

		source.buffer = buffer;
		source.playbackRate.setValueAtTime(audio.playbackRate, audio.startTime);
		audio.startTime = context.currentTime;
		console.log(context.currentTime);
		source.start(audio.startTime, 0);
	};

	scene.push(ball);
	objects.push(ball);
}

const render = () => {
	const time = Date.now();

	for (let i = 0; i < objects.length; i++) {
		const ball = objects[i];
		const previousHeight = ball.y;
		const al = i * offset + time * speed;

		ball.y = Math.abs(Math.sin(0.5 * al) * height);

		if (ball.y === previousHeight) {
			continue;
		}

		if (ball.y < previousHeight) {
			ball.down = true;
		} else if (ball.down) {
			// If ball changed direction from down to up
			ball.audio.play();
			ball.down = false;
		}
	}
};

setInterval(() => render(), 16);
