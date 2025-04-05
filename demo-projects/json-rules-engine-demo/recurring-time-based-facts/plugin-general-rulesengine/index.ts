import Moleculer, { Context, Service, ServiceBroker } from "moleculer";
import * as PluginConfig from "./config";
import {
  RuleActionManager,
  RuleManager,
  RulesConditionManager,
} from "./actions/manage-rules";
import { RuleRegistry } from "./helpers/rules-engine-helper";
import { _RulesEngine } from "./rules-engine";
import type { IRoutineSet } from "./models/kiotp_rules_engine_model";
import { GetFactsTriggerAction } from "./actions/get-facts-triggers";
import { GetVersionStr } from "../types";
import { AsyncDelay } from "../types";
import { AddFacts } from "./models/kiotp_facts_triggers_discovery";
import { AddTriggers } from "./models/kiotp_facts_triggers_discovery";
import {
  addEngineMetaIntoContext,
  executeRoutines,
  isFactModifiedByAnotherRule,
  processDelay,
} from "../utils/processEvent";
export class PluginService extends Service {
  mongoFlag: boolean;
  constructor(broker: ServiceBroker) {
    super(broker);
    this.mongoFlag = true;
    this.parseServiceSchema({
      name: PluginConfig.NAME,
      version: GetVersionStr(PluginConfig.VERSION),
      dependencies: [],
      settings: {
        upperCase: true,
      },
      actions: {
        GetPluginInfo: () => {
          return PluginConfig;
        },
        AddRule: RuleManager.AddRuleAction.handler,
        DeleteRule: RuleManager.RemoveRuleAction.handler,
        GetRules: RuleManager.GetRulesAction.handler,
        UpdateRule: RuleManager.UpdateRuleAction.handler,
        AddActionToRule: RuleActionManager.AddActionToRuleAction.handler,
        DeleteActionInRule:
          RuleActionManager.RemoveActionFromRuleAction.handler,
        UpdateActionInRule: RuleActionManager.UpdateActionInRuleAction.handler,
        GetActionsInRule: RuleActionManager.GetRuleActionsAction.handler,
        GetCoditionSetItems:
          RulesConditionManager.GetConditionSetAction.handler,
        AddConditionSet: RulesConditionManager.CreateConditionSet.handler,
        RemoveConditionSet: RulesConditionManager.RemoveConditionSet.handler,
        AddCondition: RulesConditionManager.AddConditionToConditionSet.handler,
        RemoveCondition:
          RulesConditionManager.RemoveConditionFromConditionSet.handler,
        UpdateCondition:
          RulesConditionManager.UpdateConditionInConditionSetAction.handler,
        AddAction: RuleActionManager.AddActionToRuleAction.handler,
        RemoveAction: RuleActionManager.RemoveActionFromRuleAction.handler,
        UpdateAction: RuleActionManager.UpdateActionInRuleAction.handler,
        GetFactsTrigger: GetFactsTriggerAction.handler,
        getMapping: RuleManager.GetMapping.handler,
        AddFacts: AddFacts,
        AddTriggers: AddTriggers,
        AsyncDelay: AsyncDelay,
      },
      methods: {
        processActions: async (
          routineSets: IRoutineSet[],
          metadata: Object
        ) => {
          for (const routineSet of routineSets) {
            if (routineSet.delay) {
              await processDelay(this.broker, routineSet.delay);
            } else if (routineSet.routines) {
              await executeRoutines(this.broker, routineSet.routines, metadata);
              broker.logger.info(
                "[RulesEngine] Finished processing trigger set"
              );
            }
          }
        },

        factChangeEventHandler: async (ctx: Moleculer.Context) => {
          broker.logger.info("[RulesEngine] Fact Change Detected");
          if (isFactModifiedByAnotherRule(broker, ctx)) {
            broker.logger.warn("[RulesEngine] Stopping the execution");
            return;
          }
          try {
            broker.logger.info("[RulesEngine] Start a new rulesEngine");
            let _engine = new _RulesEngine();
            ctx = addEngineMetaIntoContext(ctx);
            broker.logger.info("[FactChangeHandler] Context.Meta", ctx.meta);
            let engineResponse = await _engine.execute(ctx);
            if (engineResponse.events.length == 0) {
              broker.logger.info(
                "[RulesEngine] No event occured due to current fact changes."
              );
            }
            engineResponse.events.forEach(async (event) => {
              broker.logger.info(
                "[RulesEngine] Due to facts change, triggering event ",
                event.type
              );
              await this.processActions(
                event.params as IRoutineSet[],
                ctx.meta
              ); //typescript shenanigans
            });
          } catch (err) {
            broker.logger.info(
              "[RulesEngine] Error while processing fact change event",
              err
            ;
          }
          // }else{
          //   broker.logger.log("[RulesEngine] Event already executed")
          //   this.eventExecuted = false
          // }
        },
      },
      events: {
        "facts.state.changed": (ctx: Moleculer.Context) => {
          group: "some-random-group";
          broker.logger.info("forget-and-fire event");
          this.factChangeEventHandler(ctx);
        },
      },
      channels: {
        "p2.facts.state.changed": {
          group: `${this.broker.namespace}.${PluginConfig.NAME}.p2.facts.state.changed`,
          context: true, // Unless not enabled it globally
          maxRetries: 5,
          async handler(ctx: Moleculer.Context) {
            broker.logger.info(
              "[RulesEngine] Message received on channel p2.facts.state.changed"
            );
            broker.logger.info("Context.params=> ", ctx.params);
            //@ts-ignore
            this.factChangeEventHandler(ctx);
          },
        },
        "p2.task.execution.failed": {
          group: `${this.broker.namespace}.${PluginConfig.NAME}.p2.task.execution.failed`,
          context: true,
          async handler(ctx: Moleculer.Context) {
            broker.logger.info(
              "[RulesEngine] Task Execution failed for ",
              ctx.params
            );
          },
        },
      },
      created: this.serviceCreated,
    });
  }
  async serviceCreated() {
    console.info(`${PluginConfig.NAME} Created`);
    RuleRegistry.init(this.broker);
  }
}
export { PluginConfig };
