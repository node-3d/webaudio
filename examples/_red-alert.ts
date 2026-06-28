import { AudioContext } from '@node-3d/webaudio';


const context = new AudioContext();

const osc = context.createOscillator();
const oscGain = context.createGain();

const resonator = context.createOscillator();
const resonatorGain = context.createGain();
const resonanceSum = context.createGain();

const delay = [
	context.createDelay(0.04),
	context.createDelay(0.04),
	context.createDelay(0.04),
	context.createDelay(0.04),
	context.createDelay(0.04),
];

const delaySum = context.createGain();
const filterSum = context.createGain();

const filter = [
	context.createBiquadFilter(),
	context.createBiquadFilter(),
	context.createBiquadFilter(),
	context.createBiquadFilter(),
];

osc.type = 'sawtooth';
osc.frequency.value = 220;
osc.start(0);

oscGain.gain.value = 0.5;

resonator.type = 'sine';
resonator.frequency.value = 220;
resonator.start(0);

resonatorGain.gain.value = 0.0;

resonanceSum.gain.value = 0.5;

// oscillator drives resonator frequency
osc.connect(resonator.frequency);

// osc -. oscGain -------------+
// resonator . resonatorGain --+-. resonanceSum
osc.connect(oscGain);
oscGain.connect(resonanceSum);
resonator.connect(resonatorGain);
resonatorGain.connect(resonanceSum);

delaySum.gain.value = 0.2;

// resonanceSum --+-. delay0 --+
//                +-. delay1 --+
//                + ...    .. --+
//                +-. delay4 --+--. delaySum
const delayTimes = [0.015, 0.022, 0.035, 0.024, 0.011] as const;
for (let i = 0; i < delayTimes.length; i++) {
	const d = delayTimes[i];
	delay[i].delayTime.value = d;
	resonanceSum.connect(delay[i]);
	delay[i].connect(delaySum);
}

filterSum.gain.value = 0.2;

// delaySum --+-. filter0 --+
//            +-. filter1 --+
//            +-. filter2 --+
//            +-. filter3 --+
//            +--------------+---. filterSum
//
delaySum.connect(filterSum);

const filterFrequencies = [740, 1400, 1500, 1600] as const;
for (let i = 0; i < filterFrequencies.length; i++) {
	const f = filterFrequencies[i];
	filter[i].frequency.value = f;
	filter[i].Q.value = 12;
	delaySum.connect(filter[i]);
	filter[i].connect(filterSum);
}

// filterSum -. destination
filterSum.connect(context.destination);

// 6 sec
await new Promise((res) => { setTimeout(res, 6000); });

console.log('DONE');
