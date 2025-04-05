import { Context } from "moleculer";
import * as RulesDbModels from "../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../helpers/rules-engine-helper";
import { RuleManager } from "..";
export namespace IAddRuleAction {
  export interface Request extends RulesDbModels.IRule {
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class GetMapping {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IAddRuleAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(ctx: Context): Promise<Record<string, string[]>> {
    console.log(ctx.params, ctx.id);
    let mapping: Record<string, string[]> = {};

    try {
      const allRules = await RuleManager.GetRulesAction.handler();
      const rulesData = allRules.data;

      for (let rules of rulesData) {
        //@ts-ignore
        if(rules.id == ctx.params.id){
          continue
        }
        const rulesMapping = GetMapping.extractSceneIdsFromRule(rules);

        // Merge rulesMapping into the main mapping
        for (const key of Object.keys(rulesMapping)) {
          if (mapping[key]) {
            // Merge and remove duplicates
            mapping[key] = Array.from(new Set([...mapping[key], ...rulesMapping[key]]));
          } else {
            mapping[key] = rulesMapping[key];
          }
        }
      }
    } catch (err) {
      console.log("Error in rulesAndSceneMapping:", err);
    }

    return mapping;
  }

  static extractSceneIdsFromRule(rules: any): Record<string, string[]> {
    const rulesMapping: Record<string, string[]> = {};
  
    // Check if rules, event, and params are defined
    if (!rules || !rules.event || !rules.event.params) {
      // console.log("Invalid rules structure: missing event or params");
      return rulesMapping;
    }
  
    const actions = rules.event.params.actions || [];
  
    // Check if conditions are defined and are an array
    if (!Array.isArray(rules.conditions)) {
      // console.log("Invalid rules structure: conditions should be an array");
      return rulesMapping;
    }
  
    // Collect scene IDs from conditions
    for (const condition of rules.conditions) {
      if (!Array.isArray(condition)) {
        // console.log("Invalid condition structure: condition should be an array", condition);
        continue;
      }
  
      for (const action of condition) {
        if (!action || typeof action !== 'object') {
          // console.log("Invalid action structure: action should be an object", action);
          continue;
        }
  
        if (action.factName?.includes("media-scene-state") || action.factName?.includes("current-scene-state")) {
          const sceneId: string | undefined = action.factValue;
          if (sceneId) {
            rulesMapping[sceneId] = [];
          }
        }
      }
    }
  
    // Collect scene IDs from actions
    const data = actions
      .map((routine: any) => {
        if (!routine || !routine.actionData || !routine.actionData.customActionData) {
          // console.log("Invalid routine structure: missing actionData or customActionData", routine);
          return undefined;
        }
        return routine.actionData.customActionData.sceneId;
      })
      .filter((sceneId: string | undefined) => sceneId !== undefined) as string[];
  
    // Update rulesMapping with collected scene IDs
    for (const key of Object.keys(rulesMapping)) {
      rulesMapping[key] = data;
    }
  
    return rulesMapping;
  }

  static async isCircular(input1: any, input2: any) {
    const mergedGraph: any = { ...input1 };
    for (let key in input2) {
      if (!mergedGraph[key]) {
        mergedGraph[key] = [];
      }
      mergedGraph[key] = [...new Set([...mergedGraph[key], ...input2[key]])]; 
    }
      const visited = new Set<string>(); 
    const inRecursionStack = new Set<string>();
  
    function dfs(node: string): boolean {
      if (inRecursionStack.has(node)) {
        return true;
      }
      
      if (visited.has(node)) {
        return false;
      }
  
      inRecursionStack.add(node);
  
      // Explore all the neighbors of the current node
      if (mergedGraph[node]) {
        for (let neighbor of mergedGraph[node]) {
          if (dfs(neighbor)) {
            return true;
          }
        }
      }
      inRecursionStack.delete(node);
      visited.add(node);
      return false;
    }
  
    for (let node in mergedGraph) {
      if (!visited.has(node)) {
        if (dfs(node)) {
          return true;
        }
      }
    }
    return false; 
}

}

export { GetMapping };
