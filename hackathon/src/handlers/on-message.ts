import { Engine } from 'json-rules-engine';
import { runEngine } from '../rules/engine.js';
import {
  CameraMotionEvent,
  EventInfoResponse,
  EventOccurrence,
  eventInfoResponseSchema
} from '../types.js';

async function fetchEventInfo(event: CameraMotionEvent): Promise<EventInfoResponse> {
  const date = event.timestamp instanceof Date ? event.timestamp : new Date(event.timestamp);
  const payload = {
    eventId: event.eventId,
    eventType: event.eventType,
    hourOfDay: date.getHours(),
    dayOfWeek: date.getDay()
  };

  const response = await fetch('http://100.82.115.91:3000/api/events/query', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(payload)
  });

  if (!response.ok) {
    throw new Error(`event-info request failed with status ${response.status}`);
  }

  const data = await response.json();
  const parsed = eventInfoResponseSchema.safeParse(data);
  console.log("Received event info response:", parsed);
  if (!parsed.success) {
    throw new Error(`Invalid event-info response: ${parsed.error.message}`);
  }
  return parsed.data;
}

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
  let info: EventInfoResponse;
  try {
    info = await fetchEventInfo(event);
  } catch (error) {
    console.error('Failed to fetch event info', error);
    return;
  }

  const facts = {
    ...event,
    occurrence: info.data.occurrence,
    dismissible: info.data.dismissible,
    overallCount: info.data.overallCount
  } as Record<string, unknown>;

  const { events } = await runEngine(engineRef.current, facts);

  // Only the first matched rule should fire
  if (events.length > 0) {
    const ruleEvent = events[0];
    const decision: Decision = {
      ruleEventType: ruleEvent.type,
      params: ruleEvent.params as Record<string, unknown> | undefined
    };

    // Send rule decision to UI
    await sendToUI({
      ...facts,
      ruleEventType: ruleEvent.type,
      params: ruleEvent.params
    });

    if (emitDecision) {
      await emitDecision(decision);
    }

    console.log('Rule matched', decision);
  }
}

async function sendToUI(data: any) {
  try {
    await fetch('http://localhost:8080/api/events', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(data)
    });
  } catch (error) {
    // UI server might not be running, just log and continue
    console.debug('Could not send to UI server:', error);
  }
}
