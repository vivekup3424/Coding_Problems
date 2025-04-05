import Moleculer, {Context, Service,ServiceBroker, type ServiceSchema, type ServiceSettingSchema } from "moleculer";
import * as PluginConfig from "./config"
import { AsyncDelay, GetVersionStr } from "../types";
import { GetFactsTriggerAction } from "./actions/get-facts-trigger";
import { GetLightState } from "./actions/GetLightState";
import { GetLightColor } from "./actions/GetLightColor";
import { GetLightBrightness } from "./actions/GetLightBrightness";
import { LightMethods } from "./models";
import { ChangeLightBrightness } from "./actions/ChangeLightBrightness";
import { ChangeLightColor } from "./actions/ChangeLightColor";
import { ChangeLightState } from "./actions/ChangeLightState";
export class lightService extends Service{
    static broker: ServiceBroker
    constructor(_broker : ServiceBroker){
        super(_broker)
        this.broker = _broker;
        this.parseServiceSchema({
            name: PluginConfig.NAME,
            version: GetVersionStr(PluginConfig.VERSION),
            settings: {},
            dependencies: [],
            actions:{
                GetPluginInfo: () =>{
                    return PluginConfig
                },
                GetFactsTrigger: GetFactsTriggerAction.handler,
                GetLightState: GetLightState.handler,
                GetLightColor: GetLightColor.handler,
                GetLightBrightness: GetLightBrightness.handler,
                ChangeLightBrightness: ChangeLightBrightness.handler,
                ChangeLightColor: ChangeLightColor.handler,
                ChangeLightState: ChangeLightState.handler,
            },
            channels: {
                "p2.trigger-bulb-state-change": {
                  async handler(ctx:Context) {
                    console.log(
                      "------light SERVICE RECIEVED A MESSAGE-----",
                      ctx.params
                    );
                    // await AsyncDelay(2000);
                  },
                },
                "p2.trigger-bulb-brightness-change": {
                  async handler(ctx: Context) {
                    console.log(
                      "------light SPEED RECIEVED A MESSAGE-----",
                      ctx.params
                    );
                      // await AsyncDelay(2000);
                  },
                },
                "p2.trigger-bulb-color-change": {
                  async handler(ctx: Context) {
                    console.log(
                      "------light MODE RECIEVED A MESSAGE-----",
                      ctx
                    );
                      // await AsyncDelay(2000);
                  },
                },
              },
            started: this.serviceStarted,
        });
    }
    serviceStarted(){
      //add some dummy data in it
      LightMethods.insertDefaultLights()
    }
}