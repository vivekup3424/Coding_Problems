import { ServiceBroker } from "moleculer";
import { PluginService as RulesEningeService } from "./plugin-general-rulesengine";
import { brokerConfig } from "./moleculer.config";
import { FanService } from "./plugin-fan";
import { lightService as LightService } from "./plugin-lighting";
import mongoose from "mongoose";
const broker = new ServiceBroker(brokerConfig);

try {
  await mongoose.connect("mongodb://localhost:27017/calendarDB", {});
  console.log("Connected to MongoDB");
} catch (error) {
  console.error("Error connecting to MongoDB:", error);
}

const rule6 = {
  name: "TurnOnLightWhenFanOn",
  description: "If fan is on, then turn on the light.",
  conditionSets: [
    {
      name: "Fan On Check",
      conditions: [
        {
          factName: "fan-power-state",
          operation: "equal",
          factValue: "on",
          serviceId: "1.0.0.kiotp.plugins.general.fan",
          factStateAction: "GetFanState",
          params: {
            deviceId: "Fan-F1",
          },
        },
      ],
    },
  ],
  event: {
    type: "Turn on Lights, and then get context from turn on lights, to change mode of a specific fan",
    params: [
      {
        order: 0,
        routines: [
          {
            serviceId: "1.0.0.kiotp.plugins.general.lighting",
            executionName: "ChangeLightState",
            executionStrategy: "durable",
            moleculerEvent: "p2.trigger-bulb-state-change",
            customExecutionData: {
              deviceId: "Light-L2",
              LightState: "on",
            },
          },
        ],
      },
      {
        order: 1,
        delay: 1,
      },
      {
        order: 2,
        routines: [
          {
            serviceId: "1.0.0.kiotp.plugins.general.fan",
            executionName: "ChangeFanMode",
            executionStrategy: "durable",
            moleculerEvent: "p2.trigger-fan-mode-change",
            customExecutionData: {
              deviceId: "Fan-F1",
              FanMode: "turbo",
            },
          },
        ],
      },
    ],
  },
  enabled: true,
  priority: 10,
};
broker.createService(RulesEningeService);
broker.createService(FanService);
broker.createService(LightService);

broker
  .start()
  .then(async () => {
    console.log("Broker Started");
    try {
      await broker.waitForServices("1.0.0.kiotp.plugins.general.rulesengine");
      await broker.call(
        "1.0.0.kiotp.plugins.general.rulesengine.AddRule",
        rule6
      );
      console.log("Rule 6 added successfully to the rules engine");
    } catch (error) {
      console.error("Error during adding rules with the rules engine:", error);
    }
  })
  .catch((err) => {
    console.error("Error starting broker:", err);
  });
