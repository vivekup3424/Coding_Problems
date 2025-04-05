import { Context } from "moleculer";
import * as RulesDbModels from "../../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../../helpers/rules-engine-helper";
import {sendLiveEvent} from "../../../../utils"

export namespace IRemoveConditionFromConditionSet {
  export interface Request {
    conditoinId: string;
    conditionSetId: string;
    ruleId: string;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class RemoveConditionFromConditionSet {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IRemoveConditionFromConditionSet.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(
    ctx: Context
  ): Promise<IRemoveConditionFromConditionSet.Response> {
    console.log(ctx.params, ctx.id);

    try {
      let params = <IRemoveConditionFromConditionSet.Request>ctx.params;

      if (!params.ruleId)
        return {
          success: false,
          error: "ruleId is required to remove condition from condition set",
        };

      if (!params.conditoinId)
        return {
          success: false,
          error: "required conditionId",
        };

      let removeRes = await RulesDbModels.Methods.removeConditionItem(
        params.conditionSetId,
        params.conditoinId
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

export { RemoveConditionFromConditionSet };
