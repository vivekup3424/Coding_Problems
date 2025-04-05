import mongoose, { Schema, Document } from "mongoose";
import { v4 as uuidv4 } from "uuid";

// Interfaces to define the shape of our documents
interface IResponse<Data = any> {
  success: boolean;
  error?: string;
  data?: Data;
}

interface ICondition extends Document {
  name?: string;
  operation: string;
  factName: string;
  factValue: any;
  factStateAction: string;
  factPath?: string;
  serviceId: string;
  priority?: number;
  params?: object;
}

interface IExecution extends Document {
  serviceId: string;
  executionName: string;
  executionStrategy?: string;
  action?: string;
  moleculerEvent?: string;
  customExecutionData?: object;
}

interface IRuleConditionSet extends Document {
  id: string;
  name: string;
  conditions: ICondition[];
}

interface IRoutineSet extends Document {
  order: number;
  delay?: number;
  routines?: IExecution[];
}

interface IRuleEvent extends Document {
  type: string;
  params: IRoutineSet[];
}

interface IRule extends Document {
  name: string;
  description?: string;
  conditionSets?: IRuleConditionSet[];
  event: IRuleEvent;
  enabled: boolean;
  priority?: number;
}
const ConditionSchema = new Schema<ICondition>({
  name: String,
  serviceId: { type: String, required: true },
  factName: { type: String, required: true },
  operation: { type: String, required: true },
  factValue: { type: Schema.Types.Mixed, required: true },
  factStateAction: { type: String, default: "get", required: true },
  params: Object,
  factPath: String,
  priority: Number,
});

const ExecutionSchema = new Schema<IExecution>({
  serviceId: { type: String, required: true },
  executionName: { type: String, required: true },
  executionStrategy: String,
  action: String,
  moleculerEvent: String,
  customExecutionData: Object,
});

const RuleConditionSetSchema = new Schema<IRuleConditionSet>({
  name: { type: String, required: true },
  conditions: [ConditionSchema],
});
const RoutineSetSchema = new Schema<IRoutineSet>({
  order: { type: Number, required: true },
  delay: { type: Number },
  routines: [ExecutionSchema],
});

const RuleEventSchema = new Schema<IRuleEvent>({
  type: { type: String, required: true },
  params: { type: [RoutineSetSchema] },
});

const RuleSchema = new Schema<IRule>({
  name: { type: String, required: true },
  description: String,
  conditionSets: [RuleConditionSetSchema],
  event: { type: RuleEventSchema, required: true },
  enabled: { type: Boolean, default: true },
  priority: { type: Number, default: 1 },
});
const Rule = mongoose.model<IRule>("Rule", RuleSchema);

// Methods class converted to static methods on the Rule model
class RuleMethods {
  static async getRule(ruleId: string): Promise<IResponse> {
    try {
      const rule = await Rule.findOne({ id: ruleId });
      if (!rule) {
        return { success: false, error: "rule does not exist" };
      }
      return { success: true, data: rule.toObject() };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }
  static async getRules(): Promise<IResponse> {
    try {
      const rules = await Rule.find();
      const rulesAsObject = rules.map((rule) => rule.toObject());
      if (!rules) {
        return { success: false, error: "No rules found" };
      }
      return { success: true, data: rulesAsObject };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }

  static async addRule(ruleData: IRule): Promise<IResponse> {
    try {
      const existingRule = await Rule.findOne({ name: ruleData.name });

      if (existingRule) {
        console.info("[RuleMethods] Rule exists, updating:", ruleData.name);
        // Update the existing rule
        existingRule.set(ruleData);
        await existingRule.save();
        return { success: true, data: existingRule.toObject() };
      }

      console.info(
        "[RuleMethods] Rule does not exist, creating new:",
        ruleData.name
      );
      const rule = new Rule(ruleData);
      await rule.save();

      console.info("[RuleMethods] New rule successfully added:", ruleData.name);
      return { success: true, data: rule.toObject() };
    } catch (error) {
      console.error("[RuleMethods] Error while adding rule:", error);
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }

  static async removeRule(ruleId: string): Promise<IResponse> {
    try {
      const result = await Rule.deleteOne({ id: ruleId });
      if (result.deletedCount === 0) {
        return { success: false, error: "rule does not exist" };
      }
      return { success: true };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }

  static async updateRule(ruleData: Partial<IRule>): Promise<IResponse> {
    try {
      const rule = await Rule.findOneAndUpdate(
        { id: ruleData.id },
        { $set: ruleData },
        { new: true }
      );
      if (!rule) {
        return { success: false, error: "rule does not exist" };
      }
      return { success: true, data: rule.toObject() };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }
  static async addRoutineSet(
    ruleId: string,
    routineSet: IRoutineSet
  ): Promise<IResponse> {
    try {
      const rule = await Rule.findOne({ id: ruleId });
      if (!rule) {
        return { success: false, error: "rule does not exist" };
      }
      rule.event.params.push(routineSet);
      return { success: true, data: rule.event.params };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }
  static async removeRoutineSet(
    ruleId: string,
    routineSetId: string
  ): Promise<IResponse> {
    try {
      const rule = await Rule.findOne({ id: ruleId });
      if (!rule) {
        return { success: false, error: "rule does not exist" };
      }
      const actionIndex = rule.event.params.findIndex(
        (a) => a.id === routineSetId
      );
      if (actionIndex === -1) {
        return { success: false, error: "routine set does not exist" };
      }
      rule.event.params.splice(actionIndex, 1);
      return { success: true, data: rule.event.params };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }
  static async updateRoutineSet(
    ruleId: string,
    routineSet: IRoutineSet
  ): Promise<IResponse> {
    try {
      // Find the rule
      const rule = await Rule.findOne({ id: ruleId });
      if (!rule) {
        return { success: false, error: "rule does not exist" };
      }
      const actionIndex = rule.event.params.findIndex(
        (a) => a.id === routineSet.id
      );
      if (actionIndex === -1) {
        return { success: false, error: "routine set does not exist" };
      }
      // Update the action
      rule.event.params[actionIndex] = routineSet;
      return { success: true, data: rule.event.params };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }
  static async createConditionSet(
    conditionSet: IRuleConditionSet
  ): Promise<IResponse<IRuleConditionSet>> {
    console.log("Creating condition set");
    try {
      conditionSet.id = uuidv4();
      return { success: true, data: conditionSet };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }
  static async addConditionSet(
    ruleId: string,
    conditionSet: IRuleConditionSet
  ): Promise<IResponse<IRuleConditionSet[]>> {
    try {
      const rule = await Rule.findOne({ id: ruleId });
      if (!rule) {
        return { success: false, error: "rule does not exist" };
      }
      let newConditionSet = await this.createConditionSet(conditionSet);
      if (!newConditionSet.success || !newConditionSet.data) {
        return { success: false, error: "Failed to create condition set" };
      }
      if (!rule.conditionSets) {
        rule.conditionSets = [];
        rule.conditionSets.push(newConditionSet.data);
        await rule.save();
      }
      return { success: true, data: rule.conditionSets };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }

  static async deleteConditionSetFromAllRules(
    conditionSetId: string
  ): Promise<IResponse> {
    try {
      const rules = await Rule.find({ "conditions.id": conditionSetId });

      if (!rules.length) {
        return { success: false, error: "condition set does not exist" };
      }
      rules.map(async (rule) => {
        if (rule.conditionSets) {
          rule.conditionSets = rule.conditionSets.filter(
            (conditionSet) => conditionSet.id !== conditionSetId
          );
        }
        await rule.save(); //mongodb code
      });
      return { success: true };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }

  static async removeConditionSetFromRule(
    ruleId: string,
    conditionSetId: string
  ): Promise<IResponse> {
    try {
      const rule = await Rule.findOne({ id: ruleId });
      if (!rule) {
        return {
          success: false,
          error: "rule dofailed to insert rule in mongoes not exist",
        };
      }
      if (rule.conditionSets) {
        const conditionIndex = rule.conditionSets.findIndex(
          (c) => c.id === conditionSetId
        );

        if (conditionIndex === -1) {
          return { success: false, error: "condition set does not exist" };
        }

        rule.conditionSets.splice(conditionIndex, 1);
        await rule.save();
      }
      return { success: true };
    } catch (error) {
      //@ts-ignore
      return { success: false, error: error.message };
    }
  }

  static async addConditionItem(
    conditionSetId: string,
    condition: ICondition
  ): Promise<IResponse> {
    try {
      const rule = await Rule.findOne({ "conditionSets.id": conditionSetId });

      if (!rule) {
        return { success: false, error: "Rule not found" };
      }

      if (!rule.conditionSets) {
        return { success: false, error: "No condition sets exist" };
      }

      const conditionSet = rule.conditionSets.find(
        (cs) => cs.id === conditionSetId
      );

      if (!conditionSet) {
        return { success: false, error: "Condition set not found" };
      }
      condition.id = uuidv4();

      // Ensure conditions array exists
      if (!conditionSet.conditions) {
        conditionSet.conditions = [];
      }

      // Add the new condition
      conditionSet.conditions.push(condition);

      // Save the updated rule
      await rule.save();

      return {
        success: true,
        data: conditionSet.conditions,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : "Unknown error",
      };
    }
  }
  static async removeConditionItem(
    conditionSetId: string,
    conditionId: string
  ): Promise<IResponse> {
    try {
      const rule = await Rule.findOne({ "conditionSets.id": conditionSetId });

      if (!rule) {
        return { success: false, error: "Rule not found" };
      }

      if (!rule.conditionSets) {
        return { success: false, error: "No condition sets exist" };
      }

      const conditionSet = rule.conditionSets.find(
        (cs) => cs.id === conditionSetId
      );

      if (!conditionSet) {
        return { success: false, error: "Condition set not found" };
      }

      if (!conditionSet.conditions) {
        return { success: false, error: "No conditions exist in this set" };
      }

      const conditionIndex = conditionSet.conditions.findIndex(
        (cond) => cond.id === conditionId
      );

      if (conditionIndex === -1) {
        return { success: false, error: "Condition not found" };
      }

      // Remove the condition
      conditionSet.conditions.splice(conditionIndex, 1);

      // Save the updated rule
      await rule.save();

      return {
        success: true,
        data: conditionSet.conditions,
      };
    } catch (error) {
      return {
        success: false,
        error: error instanceof Error ? error.message : "Unknown error",
      };
    }
  }
}
export { Rule, RuleMethods };
export type {
  IRule,
  ICondition,
  IExecution,
  IRuleConditionSet,
  IRoutineSet,
  IRuleEvent,
  IResponse,
};
