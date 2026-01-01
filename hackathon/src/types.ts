import { z } from 'zod';

export const motionEventSchema = z.object({
  eventId: z.string(),
  eventType: z.string(),
  zone: z.string(),
  timestamp: z.coerce.date()
});

export type CameraMotionEvent = z.infer<typeof motionEventSchema>;

export type RuleEventPayload = Record<string, unknown>;

export enum EventOccurrence {
  VERY_RARE = 0,
  RARE = 1,
  OCCASIONAL = 2,
  COMMON = 3
}

export const eventInfoRequestSchema = z.object({
  eventId: z.string(),
  eventType: z.string(),
  hourOfDay: z.number(),
  dayOfWeek: z.number()
});

export const eventInfoResponseSchema = z.object({
  success: z.boolean(),
  data: z.object({
    occurrence: z.nativeEnum(EventOccurrence),
    dismissible: z.boolean(),
    overallCount: z.number()
  })
});

export type EventInfoResponse = z.infer<typeof eventInfoResponseSchema>;
