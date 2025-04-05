import { Context } from "moleculer";
import * as RulesDbModels from "../../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../../helpers/rules-engine-helper";
// import { RulesEngineManager } from "../../../../rules-engine";
import {sendLiveEvent} from "../../../../utils"

export namespace IUpdateConditionInConditionSetAction {
  export interface Request {
    conditionSetId: string;
    condition: RulesDbModels.IRuleConditions;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class UpdateConditionInConditionSetAction {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IUpdateConditionInConditionSetAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(
    ctx: Context
  ): Promise<IUpdateConditionInConditionSetAction.Response> {
    console.log(ctx.params, ctx.id);
    try {
      let params = <IUpdateConditionInConditionSetAction.Request>ctx.params;

      if (!params.conditionSetId)
        return {
          success: false,
          error:
            "conditionSetId is required to update condition in conditionSet",
        };
      if (!params.condition.id)
        return {
          success: false,
          error: "condition.id is required to update condition in conditionSet",
        };

      let res = await RulesDbModels.Methods.updateConditionItem(
        params.conditionSetId,
        params.condition
      );


      if(res.success){

        RuleRegistry.updateRules()
      }
      sendLiveEvent(ctx, "update", "rules")

      // await RulesEngineManager.setUpRuleEngines(ctx.broker)

      return res;
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { UpdateConditionInConditionSetAction };
