import { Context } from "moleculer";
import * as RulesDbModels from "../../../../models/kiotp_rules_engine_model";
import { RuleConditionOperations } from "../../constants";
import { RuleRegistry } from "../../../../helpers/rules-engine-helper";

export namespace IAddConditionToConditionSet {
  export interface Request {
    condition: RulesDbModels.ICondition;
    conditionSetId: string;
    ruleId: string;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class AddConditionToConditionSet {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IAddConditionToConditionSet.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(
    ctx: Context
  ): Promise<IAddConditionToConditionSet.Response> {
    console.log(ctx.params, ctx.id);

    try {
      let params = <IAddConditionToConditionSet.Request>ctx.params;

      if (!params.ruleId)
        return {
          success: false,
          error: "ruleId is required to add condition to condition set",
        };

      if (params.condition.factName) {
        if (!params.condition.operation)
          return {
            success: false,
            error: "required condition.operation",
          };

        if (!RuleConditionOperations.validOperation(params.condition.operation))
          return {
            success: false,
            error: `invalid operation field, valid operations are - ${RuleConditionOperations.GetOperations()}`,
          };

        if (!params.condition.factValue && params.condition.factValue != 0)
          return {
            success: false,
            error: "data is required when you pass a key to add the condition",
          };
      }

      let res = await RulesDbModels.RuleMethods.addConditionItem(
        params.conditionSetId,
        params.condition
      );

      if(res.success) {

        RuleRegistry.updateRules()
      }

      return res;
    } catch (err) {
      return {
        success: false,
        error: err?.toString(),
      };
    }
  }
}

export { AddConditionToConditionSet };
