import { Context } from "moleculer";
import * as RulesDbModels from "../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../helpers/rules-engine-helper";
import {sendLiveEvent} from "../../../utils"

export namespace IRemoveActionFromRuleAction {
  export interface Request {
    ruleId: string;
    actionId: string;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class RemoveActionFromRuleAction {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IRemoveActionFromRuleAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(
    ctx: Context
  ): Promise<IRemoveActionFromRuleAction.Response> {
    console.log(ctx.params, ctx.id);
    try {
      let params = <IRemoveActionFromRuleAction.Request>ctx.params;

      if (!params.ruleId || !params.actionId)
        return {
          success: false,
          error:
            "ruleId and actionId is required to remove action from the rule",
        };

      let removeRes = await RulesDbModels.RuleMethods.removeAction(
        params.ruleId,
        params.actionId
      );

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

export { RemoveActionFromRuleAction };
