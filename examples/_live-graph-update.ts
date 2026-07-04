import { AudioContext } from '@node-3d/webaudio';

const context = new AudioContext();

const oscillator1 = context.createOscillator();
const oscillator2 = context.createOscillator();

const gain = context.createGain();
gain.gain.value = 0.5;

// osc -> gain -> destination
console.log('Connect: osc1 -> gain');
oscillator1.connect(gain);
gain.connect(context.destination);

oscillator1.type = 'sine';
oscillator1.frequency.value = 220;
oscillator1.start(0);

oscillator2.type = 'sine';
oscillator2.frequency.value = 440;
oscillator2.start(0);

for (let i = 0; i < 8; i++) {
	// oxlint-disable-next-line no-await-in-loop
	await new Promise((res) => {
		setTimeout(res, 500);
	});
	console.log('Connect: osc2 -> gain');
	oscillator2.connect(gain);
	oscillator1.disconnect();

	// oxlint-disable-next-line no-await-in-loop
	await new Promise((res) => {
		setTimeout(res, 500);
	});
	console.log('Connect: osc1 -> gain');
	oscillator1.connect(gain);
	oscillator2.disconnect();
}

console.log('DONE');
