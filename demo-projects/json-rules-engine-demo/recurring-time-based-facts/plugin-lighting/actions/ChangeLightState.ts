import type { Context } from "moleculer";
import { AsyncDelay, type IResponse } from "../../types";
import { LightMethods} from "../models";
import { FACTS } from "../constants";
import { v4 } from "uuid";

export class ChangeLightState {
  static async handler(ctx: Context): Promise<IResponse> {
    try {
      //@ts-ignore
      const { deviceId, LightState } = ctx.params;
      const updatedLight = await LightMethods.updateState(deviceId, LightState);
      if (!updatedLight) {
        return { success: false,error: "Light not found" };
      }
      ctx.broker.sendToChannel("p2.facts.state.changed", {
        facts: [FACTS.LIGHT_STATE],
      },{ctx});
      return { success: true, data: updatedLight};
    } catch (err) {
      console.error("[ChangeLightState] Error:", err);
      return { success: false, error: err?.toString() };
    }
  }
}

