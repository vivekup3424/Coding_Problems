import { Context } from "moleculer";
import { RuleMethods, IAction } from "../../../models/kiotp_rules_engine_model";
import { RuleRegistry } from "../../../helpers/rules-engine-helper";
import { ObjectId } from "mongodb";

// Define request and response interfaces with proper typing
export namespace IAddActionToRuleAction {
  export interface Request {
    ruleId: string;
    action: IAction;
  }

  export interface Response<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
  }
}

// Helper function to safely extract error messages
function getErrorMessage(error: unknown): string {
  if (error instanceof Error) {
    return error.message;
  }
  if (error && typeof error === 'object' && 'message' in error) {
    return String(error.message);
  }
  if (typeof error === 'string') {
    return error;
  }
  return 'An unknown error occurred';
}

// Helper function to validate request parameters
function validateRequest(params: IAddActionToRuleAction.Request): { isValid: boolean; error?: string } {
  if (!params.ruleId?.trim()) {
    return {
      isValid: false,
      error: "ruleId is required to add action"
    };
  }

  if (!params.action?.name?.trim()) {
    return {
      isValid: false,
      error: "action.name is required to add action"
    };
  }

  return { isValid: true };
}

class AddActionToRuleAction {
  static params = {
    ruleId: "string",
    action: {
      type: "object",
      props: {
        name: "string",
        // Add other required action properties here
      }
    }
  };

  static hooks = {
    before(ctx: Context<IAddActionToRuleAction.Request>) {
      try {
        console.log("Before hook executing with params:", ctx.params);
        // You can add additional validation or transformation logic here
      } catch (error: unknown) {
        console.error("Error in before hook:", getErrorMessage(error));
      }
    },

    after(ctx: Context<IAddActionToRuleAction.Request>, res: IAddActionToRuleAction.Response) {
      try {
        console.log("After hook executing with result:", res);
        return res;
      } catch (error: unknown) {
        console.error("Error in after hook:", getErrorMessage(error));
        return res;
      }
    },
  };

  static async handler(ctx: Context<IAddActionToRuleAction.Request>): Promise<IAddActionToRuleAction.Response> {
    try {
      // Log the incoming request
      console.log("Handling action request:", { params: ctx.params, id: ctx.id });

      // Validate request parameters
      const validation = validateRequest(ctx.params);
      if (!validation.isValid) {
        return {
          success: false,
          error: validation.error
        };
      }

      // Generate new ObjectId for the action
      ctx.params.action.id = new ObjectId().toHexString();

      // Add action to rule
      const addResult = await RuleMethods.addAction(
        ctx.params.ruleId,
        ctx.params.action
      );

      // Update rules if action was added successfully
      if (addResult.success) {
        try {
          await RuleRegistry.updateRules();
        } catch (updateError: unknown) {
          console.error("Failed to update rules:", getErrorMessage(updateError));
          // Note: We don't return error here as the action was already added successfully
        }
      }

      return addResult;

    } catch (error: unknown) {
      // Log the error for debugging
      console.error("Error in AddActionToRuleAction handler:", getErrorMessage(error));

      // Return a formatted error response
      return {
        success: false,
        error: getErrorMessage(error)
      };
    }
  }
}

export { AddActionToRuleAction };