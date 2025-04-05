import { Context } from "moleculer";
import * as RulesDbModels from "../../../models/kiotp_rules_engine_model";

export namespace IGetRulesAction {
  export interface Request {}

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class GetRulesAction {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IGetRulesAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(): Promise<IGetRulesAction.Response> {
    try {
      let rules = (await RulesDbModels.RuleMethods.getRules()).data;
      return { success: true, data: rules };
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { GetRulesAction };
