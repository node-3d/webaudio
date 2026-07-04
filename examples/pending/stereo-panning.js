import { AudioContext } from '..';

/* eslint-disable */
// 'use strict';

//

// (async () => { try {

//         auto context = lab::MakeRealtimeAudioContext();

//         std::shared_ptr<AudioBus> audioClip = MakeBusFromFile("samples/trainrolling.wav", false);
//         std::shared_ptr<SampledAudioNode> audioClipNode = std::make_shared<SampledAudioNode>();
//         auto stereoPanner = std::make_shared<StereoPannerNode>(context->sampleRate());

//         {
//             ContextRenderLock r(context.get(), "Stereo Panning");

//             audioClipNode->setBus(r, audioClip);
//             context->connect(stereoPanner, audioClipNode, 0, 0);
//             audioClipNode->start(0.0f);

//             context->connect(context->destination(), stereoPanner, 0, 0);
//         }

//         if (audioClipNode)
//         {
//             audioClipNode->setLoop(true);

//             const int seconds = 8;

//             std::thread controlThreadTest([&stereoPanner, seconds]()
//             {
//                 float halfTime = seconds * 0.5f;
//                 for (float i = 0; i < seconds; i += 0.01f)
//                 {
//                     float x = (i - halfTime) / halfTime;
//                     stereoPanner->pan()->setValue(x);
//                     std::this_thread::sleep_for(std::chrono::milliseconds(10));
//                 }
//             });

//             std::this_thread::sleep_for(std::chrono::seconds(seconds));

//             controlThreadTest.join();
//         }
//         else
//         {
//             std::cerr << std::endl << "Couldn't initialize train node to play" << std::endl;
//         }

// 	console.log('DONE');

// } catch (e) { console.error(e); } })();
