import { AudioContext } from '..';

/* eslint-disable */
// 'use strict';

// 

// (async () => { try {
	
//         auto context = lab::MakeRealtimeAudioContext();
        
//         std::shared_ptr<OscillatorNode> modulator;
//         std::shared_ptr<GainNode> modulatorGain;
//         std::shared_ptr<OscillatorNode> osc;
//         std::shared_ptr<ADSRNode> trigger;
    
//         std::shared_ptr<GainNode> signalGain;
//         std::shared_ptr<GainNode> feedbackTap;
//         std::shared_ptr<DelayNode> chainDelay;
        
//         {
//             modulator = std::make_shared<OscillatorNode>(context->sampleRate());
//             modulator->setType(OscillatorType::SQUARE);
//             modulator->start(0);
            
//             modulatorGain = std::make_shared<GainNode>();
            
//             osc = std::make_shared<OscillatorNode>(context->sampleRate());
//             osc->setType(OscillatorType::SQUARE);
//             osc->frequency()->setValue(300);
//             osc->start(0);
            
//             trigger = std::make_shared<ADSRNode>();

//             signalGain = std::make_shared<GainNode>();
//             signalGain->gain()->setValue(1.0f);
            
//             feedbackTap = std::make_shared<GainNode>();
//             feedbackTap->gain()->setValue(0.5f);
            
//             chainDelay = std::make_shared<DelayNode>(context->sampleRate(), 4);
//             chainDelay->delayTime()->setValue(0.0f); // passthrough delay, not sure if this has the same DSP semantic as ChucK
            
//             // Set up processing chain:
//             context->connect(modulatorGain, modulator, 0, 0);                   // Modulator to Gain
//             context->connectParam(osc->frequency(), modulatorGain, 0);          // Gain to frequency parameter
//             context->connect(trigger, osc, 0, 0);                               // Osc to ADSR
//             context->connect(signalGain, trigger, 0, 0);                        // ADSR to signalGain
//             context->connect(feedbackTap, signalGain, 0, 0);                    // Signal to Feedback
//             context->connect(chainDelay, feedbackTap, 0, 0);                    // Feedback to Delay
//             context->connect(signalGain, chainDelay, 0, 0);                     // Delay to signalGain
//             context->connect(context->destination(), signalGain, 0, 0);         // signalGain to DAC
//         }
        
//         int now = 0;
//         while (true)
//         {
//             float cF = (float)std::uniform_int_distribution<int>(80, 440)(randomgenerator);
//             osc->frequency()->setValue(cF);

//             float f = (float) std::uniform_int_distribution<int>(4, 512)(randomgenerator);
//             modulator->frequency()->setValue(f);
//             std::cout << "Modulator Frequency: " << f << std::endl;
            
//             float g = (float) std::uniform_int_distribution<int>(16, 1024)(randomgenerator);
//             modulatorGain->gain()->setValue(g);
//             std::cout << "Gain: " << g << std::endl;
            
//             trigger->noteOn(now);
//             trigger->set((std::uniform_real_distribution<float>(0.25f, 0.5f)(randomgenerator)), 0.50f, 0.50f, 0, 0);

//             auto nextDelay = 512;
//             now += nextDelay;
        
//             std::this_thread::sleep_for(std::chrono::milliseconds(nextDelay));
//         };
	
// 	console.log('DONE');
	
// } catch (e) { console.error(e); } })();

