import { Context } from "moleculer";
import * as RulesDbModels from "../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../helpers/rules-engine-helper";
import {sendLiveEvent} from "../../../utils"

export namespace IUpdateActionInRuleAction {
  export interface Request {
    ruleId: string;
    action: RulesDbModels.IAction
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class UpdateActionInRuleAction {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IUpdateActionInRuleAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(
    ctx: Context
  ): Promise<IUpdateActionInRuleAction.Response> {
    console.log(ctx.params, ctx.id);

    try {
      let params = <IUpdateActionInRuleAction.Request>ctx.params;

      if (!params.ruleId || !params.action.id)
        return {
          success: false,
          error: "ruleId and action.id is required to update action",
        };

          RuleRegistry.updateRules()
        

      return await RulesDbModels.RuleMethods.updateAction(
        params.ruleId,
        params.action
      );
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { UpdateActionInRuleAction };
