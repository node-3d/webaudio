import { inspect } from 'node:util';
import type { TAudioEventCallbackList } from './native.ts';
declare const AudioParam: import("./native.ts").TAudioParamConstructor;
declare class JsAudioParam extends AudioParam {
    get onerror(): TAudioEventCallbackList;
    set onerror(cb: TAudioEventCallbackList);
    get onended(): TAudioEventCallbackList;
    set onended(cb: TAudioEventCallbackList);
    [inspect.custom](): string;
    toString(): string;
}
export { JsAudioParam as AudioParam };
