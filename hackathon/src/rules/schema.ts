import { z } from 'zod';

const conditionsSchema = z
  .object({
    all: z.array(z.any()).optional(),
    any: z.array(z.any()).optional()
  })
  .refine(value => value.all !== undefined || value.any !== undefined, {
    message: 'conditions must include all or any'
  });

const eventSchema = z.object({
  type: z.string(),
  params: z.record(z.any()).optional()
});

export const ruleSchema = z
  .object({
    name: z.string(),
    conditions: conditionsSchema,
    event: eventSchema,
    priority: z.number().optional(),
    enabled: z.boolean().default(true)
  })
  .passthrough();

export const rulesFileSchema = z.array(ruleSchema);

export type RuleConfig = z.infer<typeof ruleSchema>;

export function validateRules(candidate: unknown): RuleConfig[] {
  const result = rulesFileSchema.safeParse(candidate);
  if (!result.success) {
    const message = result.error.issues.map(issue => issue.message).join('; ');
    throw new Error(`Invalid rules file: ${message}`);
  }
  return result.data.filter(rule => rule.enabled !== false);
}
