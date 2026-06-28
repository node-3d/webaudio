import type { EventEmitter } from 'node:events';
import type { TAudioEventCallbackList } from './native.ts';
export declare const setEventCallbacks: (emitter: EventEmitter, eventName: string, callbacks: TAudioEventCallbackList) => void;
