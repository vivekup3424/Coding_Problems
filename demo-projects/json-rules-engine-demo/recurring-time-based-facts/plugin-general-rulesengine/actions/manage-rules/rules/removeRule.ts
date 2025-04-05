import { Context } from "moleculer";
import * as RulesDbModels from "../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../helpers/rules-engine-helper";

export namespace IRemoveRuleAction {
  export interface Request {
    ruleId: string;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class RemoveRuleAction {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IRemoveRuleAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(ctx: Context): Promise<IRemoveRuleAction.Response> {
    console.log(ctx.params, ctx.id);

    try {
      let params = <IRemoveRuleAction.Request>ctx.params;

      if (!params.ruleId)
        return {
          success: false,
          error: "ruleId is required to delete the rule",
        };

      let removeRes = await RulesDbModels.RuleMethods.removeRule(params.ruleId);

      if(removeRes.success){
        RuleRegistry.updateRules()
      }

      return removeRes
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { RemoveRuleAction };
