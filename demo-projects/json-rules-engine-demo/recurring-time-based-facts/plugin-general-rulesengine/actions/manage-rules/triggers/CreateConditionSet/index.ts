import { Context } from "moleculer";
import * as RulesDbModels from "../../../../models/kiotp_rules_engine_model";
import {sendLiveEvent} from "../../../../utils"

export namespace ICreateConditionSet {
  export interface Request {
    ruleId: string;
    conditionSet: {
      name?: string;
    };
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class CreateConditionSet {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: ICreateConditionSet.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(ctx: Context): Promise<ICreateConditionSet.Response> {
    console.log(ctx.params, ctx.id);

    try {
      let params = <ICreateConditionSet.Request>ctx.params;

      if (!params.ruleId)
        return {
          success: false,
          error: "ruleId is required to create condition set",
        };
        sendLiveEvent(ctx, "update", "rules")

      return await RulesDbModels.Methods.addConditionSet(
        params.ruleId,
        params.conditionSet
      );
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { CreateConditionSet };
