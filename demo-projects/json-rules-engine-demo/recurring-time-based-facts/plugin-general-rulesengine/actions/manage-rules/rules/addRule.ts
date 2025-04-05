import { Context } from "moleculer";
import * as RulesDbModels from "../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../helpers/rules-engine-helper";
import { GetMapping } from "./getMapping";
import mongoose from "mongoose";
import type { IRule } from "../../../models/kiotp_rules_engine_model";

export namespace IAddRuleAction {
  export interface Request extends RulesDbModels.IRule {
    name: string;
    description: string;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class AddRuleAction {
  static hooks = {
    before(ctx: Context) {
      console.info("[AddRuleAction] Before Hook - Incoming Params:", JSON.stringify(ctx.params, null, 2));
    },
    after(ctx: Context, res: IAddRuleAction.Response) {
      console.info("[AddRuleAction] After Hook - Params:", JSON.stringify(ctx.params, null, 2), "Response:", JSON.stringify(res, null, 2));
      return res;
    },
  };

  static async handler(ctx: Context): Promise<IAddRuleAction.Response> {
    // console.info("[AddRuleAction] Handler - Processing Rule Addition", "Context ID:", ctx.id, "Params:", JSON.stringify(ctx.params, null, 2));
    try {
      let rule = <IAddRuleAction.Request>ctx.params;

      if (!rule.name) {
        console.warn("[AddRuleAction] Validation Failed - Missing Rule Name");
        return {
          success: false,
          error: "rule.name is required to create rule",
        };
      }

      console.info("[AddRuleAction] Attempting to Insert Rule into MongoDB");
      let addRes = await RulesDbModels.RuleMethods.addRule(rule);

      if (addRes.success) {
        console.info("[AddRuleAction] Rule Successfully Inserted into MongoDB");
        RuleRegistry.updateRules();
      } else {
        console.error("[AddRuleAction] Rule Insertion Failed", "Error:", addRes.error);
      }
      return addRes;
    } catch (err) {
      console.error("[AddRuleAction] Exception Encountered While Adding Rule", "Error:", err);
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { AddRuleAction };
