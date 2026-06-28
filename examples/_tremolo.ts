import { AudioContext } from '@node-3d/webaudio';


const context = new AudioContext();

const modulator = context.createOscillator();
modulator.type = 'sine';
modulator.start(0);
modulator.frequency.value = 4;

const modulatorGain = context.createGain();
modulatorGain.gain.value = 10;

const osc = context.createOscillator();
osc.type = 'triangle';
osc.start(0);
osc.frequency.value = 440;

const gain = context.createGain();
gain.gain.value = 0.5;

// Set up processing chain
// modulator > modulatorGain ---> osc frequency
//                                osc > context
modulator.connect(modulatorGain);
modulatorGain.connect(osc.frequency);
osc.connect(gain);
gain.connect(context.destination);

// 30 sec
await new Promise((res) => { setTimeout(res, 30000); });

console.log('DONE');
