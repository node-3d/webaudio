import type { EventEmitter } from 'node:events';
import type { TAudioEventCallbackList } from './native.ts';

export const setEventCallbacks = (
	emitter: EventEmitter,
	eventName: string,
	callbacks: TAudioEventCallbackList,
): void => {
	if (!callbacks) {
		emitter.removeAllListeners(eventName);
		return;
	}
	
	if (typeof callbacks === 'function') {
		emitter.on(eventName, callbacks);
		return;
	}
	
	for (const callback of callbacks) {
		emitter.on(eventName, callback);
	}
};
