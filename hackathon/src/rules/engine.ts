import { Engine, RuleProperties } from 'json-rules-engine';
import { RuleConfig } from './schema.js';

export interface EngineOptions {
  allowUndefinedFacts?: boolean;
}

export function buildEngine(
  rules: RuleConfig[],
  options?: EngineOptions
): Engine {
  const engine = new Engine([], {
    allowUndefinedFacts: options?.allowUndefinedFacts ?? false
  });

  rules.forEach(rule => {
    const { enabled, ...rest } = rule as RuleProperties & { enabled?: boolean };
    engine.addRule(rest);
  });

  return engine;
}

export async function runEngine(engine: Engine, facts: Record<string, unknown>) {
  const result = await engine.run(facts);
  return {
    events: result.events,
    almanac: result.almanac
  };
}
