import { Engine } from 'json-rules-engine';
import { runEngine } from '../rules/engine.js';
import { CameraMotionEvent } from '../types.js';

export interface EngineRef {
  current: Engine;
}

export interface Decision {
  ruleEventType: string;
  params?: Record<string, unknown>;
}

export async function handleMotionEvent(
  engineRef: EngineRef,
  event: CameraMotionEvent,
  emitDecision?: (decision: Decision) => Promise<void> | void
) {
  const { events } = await runEngine(engineRef.current, event as unknown as Record<string, unknown>);

  for (const ruleEvent of events) {
    const decision: Decision = {
      ruleEventType: ruleEvent.type,
      params: ruleEvent.params as Record<string, unknown> | undefined
    };

    if (emitDecision) {
      await emitDecision(decision);
    } else {
      console.log('Rule matched', decision);
    }
  }
}
