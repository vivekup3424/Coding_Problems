import { readFile } from 'fs/promises';
import { watch } from 'fs';
import { RuleConfig, validateRules } from './schema.js';

export async function loadRulesFromFile(filePath: string): Promise<RuleConfig[]> {
  const raw = await readFile(filePath, 'utf-8');
  const parsed = JSON.parse(raw);
  return validateRules(parsed);
}

export interface WatchOptions {
  debounceMs?: number;
  onError?: (error: unknown) => void;
}

export function watchRules(
  filePath: string,
  onRules: (rules: RuleConfig[]) => void,
  options?: WatchOptions
): () => void {
  const debounceMs = options?.debounceMs ?? 250;
  let timer: NodeJS.Timeout | undefined;

  const reload = async () => {
    try {
      const rules = await loadRulesFromFile(filePath);
      onRules(rules);
    } catch (error) {
      options?.onError?.(error);
    }
  };

  const watcher = watch(filePath, () => {
    if (timer) {
      clearTimeout(timer);
    }
    timer = setTimeout(reload, debounceMs);
  });

  return () => {
    watcher.close();
    if (timer) {
      clearTimeout(timer);
    }
  };
}
