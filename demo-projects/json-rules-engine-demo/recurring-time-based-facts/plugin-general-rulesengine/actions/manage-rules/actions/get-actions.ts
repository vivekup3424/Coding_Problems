import { Context } from "moleculer";
import * as RulesDbModels from "../../../models/kiotp_rules_engine_model";

export namespace IGetRuleActionsAction {
  export interface Request {
    ruleId: string;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class GetRuleActionsAction {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IGetRuleActionsAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(ctx: Context): Promise<IGetRuleActionsAction.Response> {
    console.log(ctx.params, ctx.id);
    try {
      let params = <IGetRuleActionsAction.Request>ctx.params;

      if (!params.ruleId)
        return {
          success: false,
          error: "ruleId is required to get actions of a rule",
        };

      let rule = await RulesDbModels.RuleMethods.getRule(params.ruleId);

      return {
        success: rule?.success,
        error: rule?.error,
        data: rule?.data?.actions,
      };
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { GetRuleActionsAction };
