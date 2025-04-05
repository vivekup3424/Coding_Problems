import { Context, Service, ServiceBroker } from "moleculer";
import * as PluginConfig from "./config";
import { AsyncDelay, GetVersionStr } from "../types";
import { GetFactsTriggerAction } from "./actions/get-facts-trigger";
import { GetFanState } from "./actions/GetFanState";
import { GetFanSpeed } from "./actions/GetFanSpeed";
import { GetFanMode } from "./actions/GetFanMode";
import { FanMethods } from "./models";
import { ChangeFanState } from "./actions/ChangeFanState";
import { ChangeFanMode } from "./actions/ChangeFanMode";
import { ChangeFanSpeed } from "./actions/ChangeFanSpeed";
import { FACTS } from "./constants";
export class FanService extends Service {
  static broker: ServiceBroker;
  constructor(_broker: ServiceBroker) {
    super(_broker);
    this.broker = _broker;
    this.parseServiceSchema({
      name: PluginConfig.NAME,
      version: GetVersionStr(PluginConfig.VERSION),
      settings: {
        circuitBreaker: {
          threshold: 0.3, // Fail if 30% of requests fail
          windowTime: 30, // Time window (in seconds)
        },
        retryPolicy: {
          enabled: true, // Enable automatic retries
          retries: 3, // Retry 3 times
          delay: 1000, // Initial delay: 1s
          maxDelay: 5000, // Max delay: 5s
          factor: 2, // Exponential backoff
        },
      },
      dependencies: [],
      actions: {
        GetPluginInfo: () => {
          return PluginConfig;
        },
        GetFactsTrigger: GetFactsTriggerAction.handler,
        GetFanState: GetFanState.handler,
        GetFanSpeed: GetFanSpeed.handler,
        GetFanMode: GetFanMode.handler,
        ChangeFanState: ChangeFanState.handler,
        ChangeFanMode: ChangeFanMode.handler,
        ChangeFanSpeed: ChangeFanSpeed.handler,
      },
      channels: {
        "p2.trigger-fan-state-change": {
          async handler(ctx: Context) {
            await ChangeFanState.handler(ctx);
          },
        },
        "p2.trigger-fan-speed-change": {
          async handler(ctx: Context) {
            await ChangeFanSpeed.handler(ctx);
          },
        },
        "p2.trigger-fan-mode-change": {
          async handler(ctx: Context) {
            await ChangeFanMode.handler(ctx);
          },
        },
      },
      started: this.serviceStarted,
    });
  }
  async serviceStarted() {
    //inserts some dummy values for empty collecetions
    FanMethods.insertDefaultFans();
    setTimeout(() => {
      this.broker.sendToChannel(
        "p2.facts.state.changed",
        {
          facts: [FACTS.FAN_STATE],
        },
        {
          meta: {},
        }
      );
    }, 2000);
  }
}
