import { inspect } from 'node:util';
declare const AudioBuffer: import("./native.ts").TNativeEs5Constructor<[context: import("./native.ts").TBaseAudioContext, source?: Readonly<{
    length?: number;
    numberOfChannels?: number;
    sampleRate?: number;
}> | import("./native.ts").TNativeExternal | undefined], import("./native.ts").TAudioBuffer>;
declare class JsAudioBuffer extends AudioBuffer {
    [inspect.custom](): string;
    toString(): string;
}
export { JsAudioBuffer as AudioBuffer };
