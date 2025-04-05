import { Context } from "moleculer";
import * as RulesDbModels from "../../../../models/kiotp_rules_engine_model";

export namespace IGetConditionSetAction {
  export interface Request {
    conditionSetId: string;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class GetConditionSetAction {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IGetConditionSetAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(ctx: Context): Promise<IGetConditionSetAction.Response> {
    console.log(ctx.params, ctx.id);

    try {
      let params = <IGetConditionSetAction.Request>ctx.params;

      if (!params.conditionSetId)
        return {
          success: false,
          error: "conditionSetId is required to get condition set",
        };

      return await RulesDbModels.Methods.getConditionSet(params.conditionSetId);
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { GetConditionSetAction };
