import { inspect } from 'node:util';
import type { TBaseAudioContext, TNativeExternal } from './native.ts';
declare const AudioListener: import("./native.ts").TNativeEs5Constructor<[context: TBaseAudioContext, listener: TNativeExternal, paramCtor: import("./native.ts").TAudioParamConstructor], import("./native.ts").TAudioListener>;
declare class JsAudioListener extends AudioListener {
    constructor(ctx: TBaseAudioContext, listener: TNativeExternal);
    [inspect.custom](): string;
    toString(): string;
}
export { JsAudioListener as AudioListener };
