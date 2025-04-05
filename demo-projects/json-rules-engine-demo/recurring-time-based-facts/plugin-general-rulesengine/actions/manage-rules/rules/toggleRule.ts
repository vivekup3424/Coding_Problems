import { Context } from "moleculer";
// import { RulesEngineManager } from "../../../rules-engine";
import * as RuleModels from "../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../helpers/rules-engine-helper";
import {sendLiveEvent} from "../../../utils"

export namespace IToggleRuleAction {
  export interface Request {
    ruleId: string;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class ToggleRuleAction {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IToggleRuleAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(ctx: Context): Promise<IToggleRuleAction.Response> {
    console.log(ctx.params, ctx.id);
    try {
      let params = <IToggleRuleAction.Request>ctx.params;

      if (!params.ruleId)
        return {
          success: false,
          error: "ruleId is required to toggle rule",
        };
      let ruleRes = await RuleModels.Methods.getRule(params.ruleId);
      let ruleToEdit = ruleRes.data;
      if (ruleRes.success) {
        if (ruleToEdit.enabled) {
          ruleToEdit.enabled = false;
        } else {
          ruleToEdit.enabled = true;
        }
        await RuleModels.Methods.updateRule(ruleToEdit);

      }
      RuleRegistry.updateRules()
      // await RulesEngineManager.toggleRule(params.ruleId);
      sendLiveEvent(ctx, "update", "rules")

      // await RulesEngineManager.setUpRuleEngines(ctx.broker)

      return {
        success: true,
      };
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { ToggleRuleAction };
