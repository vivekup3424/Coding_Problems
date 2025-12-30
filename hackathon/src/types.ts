import { z } from 'zod';

export const motionEventSchema = z.object({
  _id: z.string(),
  event_id: z.string(), // e.g., cameras.motion.person
  event_type: z.string(), // e.g., cameras
  hour_of_day: z.number(),
  day_of_week: z.number(),
  count_last_24h: z.number(),
  count_last_7d: z.number(),
  count_last_30d: z.number(),
  count_last_90d: z.number(),
  count_all_time: z.number(),
  last_occurred: z.number()
});

export type CameraMotionEvent = z.infer<typeof motionEventSchema>;

export type RuleEventPayload = Record<string, unknown>;
