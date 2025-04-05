import { Context } from "moleculer";
import * as RulesDbModels from "../../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../../helpers/rules-engine-helper";
import {sendLiveEvent} from "../../../../utils"

export namespace IRemoveConditionSet {
  export interface Request {
    ruleId: string;
    conditionSetId: string;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class RemoveConditionSet {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IRemoveConditionSet.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(ctx: Context): Promise<IRemoveConditionSet.Response> {
    console.log(ctx.params, ctx.id);

    try {
      let params = <IRemoveConditionSet.Request>ctx.params;

      if (!params.ruleId)
        return {
          success: false,
          error: "ruleId is required to remove condition set",
        };

      let removeRes = await RulesDbModels.Methods.removeConditionSet(
        params.ruleId,
        params.conditionSetId
      );

      if(removeRes.success){
        RuleRegistry.updateRules()
      }
      sendLiveEvent(ctx, "update", "rules")

      return removeRes
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { RemoveConditionSet };
