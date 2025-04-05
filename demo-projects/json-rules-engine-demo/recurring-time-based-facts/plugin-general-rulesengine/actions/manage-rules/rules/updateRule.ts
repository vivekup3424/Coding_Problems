import { Context } from "moleculer";
import * as RulesDbModels from "../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../helpers/rules-engine-helper";
import { GetMapping } from "./getMapping";

export namespace IUpdateRuleAction {
  export interface Request extends RulesDbModels.IRule {}

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

class UpdateRuleAction {
  static params = {};

  static hooks = {
    before(ctx: Context) {
      console.log("this is before", ctx.params);
    },
    after(ctx: Context, res: IUpdateRuleAction.Response) {
      console.log("this is after", ctx.params, res);

      return res;
    },
  };

  static async handler(ctx: Context): Promise<IUpdateRuleAction.Response> {
    console.log(ctx.params, ctx.id);
    try {
      let params = <IUpdateRuleAction.Request>ctx.params;

      if (!params.name)
        return {
          success: false,
          error: "rule.name is required to update the rule",
        };
      let rulesMapping : any = await GetMapping.handler(ctx);
      let newParams : any = Object.assign({}, params);
      let conditions = {}
      if(params.conditionSets){
        conditions = params.conditionSets.map(conditionSet => conditionSet.conditions)
      }
      newParams.conditions = conditions
      let res = await RulesDbModels.RuleMethods.updateRule(params);
      
      if(res.success){
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

export { UpdateRuleAction };
