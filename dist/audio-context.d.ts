import type { TJsBaseAudioContext } from './base-audio-context.ts';
import type { TAudioContext, TAudioContextOptions, TNativeConstructor } from './native.ts';
declare const WrappedAudioContext: TNativeConstructor<[opts?: TAudioContextOptions], TAudioContext & TJsBaseAudioContext>;
export { WrappedAudioContext as AudioContext };
