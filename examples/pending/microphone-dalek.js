import { AudioContext } from '..';

/* eslint-disable */
// 'use strict';

// 

// const makeDistortionCurve = amount => {
// 	let k = typeof amount === 'number' ? amount : 50;
// 	let nSamples = 44100;
// 	let curve = new Float32Array(nSamples);
// 	let deg = Math.PI / 180;
// 	let i = 0;
// 	let x;
// 	for ( ; i < nSamples; ++i ) {
// 		x = i * 2 / nSamples - 1;
// 		curve[i] = ( 3 + k ) * x * 20 * deg / ( Math.PI + k * Math.abs(x) );
// 	}
// 	return curve;
// };

// (async () => { try {
	
// 	const context = new AudioContext();
	
// 	const vIn = context.createOscillator();
// 	vIn.frequency.value = 30;
// 	vIn.start(0);
	
// 	const vInGain = context.createGain();
// 	vInGain.gain.value = 0.5;
	
// 	const vInInverter1 = context.createGain();
// 	vInInverter1.gain.value = -1;
// 	const vInInverter2 = context.createGain();
// 	vInInverter2.gain.value = -1;
	
// 	const vInDiode1 = context.createWaveShaper();
// 	vInDiode1.curve = makeDistortionCurve(400);
// 	vInDiode1.oversample = '4x';
// 	const vInDiode2 = context.createWaveShaper();
// 	vInDiode2.curve = makeDistortionCurve(400);
// 	vInDiode2.oversample = '4x';
	
// 	const vInInverter3 = context.createGain();
// 	vInInverter3.gain.value = -1;
	
// 	// Now we create the objects on the Vc side of the graph
// 	const vcInverter1 = context.createGain();
// 	vcInverter1.gain.value = -1;
	
// 	const vcDiode3 = context.createWaveShaper();
// 	vcDiode3.curve = makeDistortionCurve(400);
// 	vcDiode3.oversample = '4x';
	
// 	const vcDiode4 = context.createWaveShaper();
// 	vcDiode4.curve = makeDistortionCurve(400);
// 	vcDiode4.oversample = '4x';
	
// 	// A gain node to control master output levels
// 	const outGain = context.createGain();
// 	outGain.gain.value = 1;
	
	
// 	// A small addition to the graph given in Parker's paper is a compressor node
// 	// immediately before the output. This ensures that the user's volume remains
// 	// somewhat constant when the distortion is increased.
// 	const compressor = context.createDynamicsCompressor();
// 	compressor.threshold.value = -14;
	
// 	// Now we connect up the graph following the block diagram above (on the web page).
// 	// When working on complex graphs it helps to have a pen and paper handy!
	
// 	//const stream = navigator.mediaDevices.getUserMedia({audio: true, video: true})
	
// 	const input = context.createMediaStreamSource(/*stream*/);
// 	input.connect(vcInverter1);
// 	input.connect(vcDiode4);
	
	
// 	vcInverter1.connect(vcDiode3);
	
// 	// Then the Vin side
// 	context.connect(vInGain, vIn, 0, 0);
// 	context.connect(vInInverter1, vInGain, 0, 0);
// 	context.connect(vcInverter1, vInGain, 0, 0);
// 	context.connect(vcDiode4.node(), vInGain, 0, 0);
	
// 	context.connect(vInInverter2, vInInverter1, 0, 0);
// 	context.connect(vInDiode2.node(), vInInverter1, 0, 0);
// 	context.connect(vInDiode1.node(), vInInverter2, 0, 0);
	
// 	// Finally connect the four diodes to the destination via the output-stage compressor and master gain node
// 	context.connect(vInInverter3, vInDiode1.node(), 0, 0);
// 	context.connect(vInInverter3, vInDiode2.node(), 0, 0);
	
// 	context.connect(compressor, vInInverter3, 0, 0);
// 	context.connect(compressor, vcDiode3.node(), 0, 0);
// 	context.connect(compressor, vcDiode4.node(), 0, 0);
	
// 	context.connect(outGain, compressor, 0, 0);
// 	context.connect(context.destination(), outGain, 0, 0);
	
// 	// 30 sec
// 	await new Promise(res => setTimeout(res, 30000));
	
// 	console.log('DONE');
	
// } catch (e) { console.error(e); } })();

