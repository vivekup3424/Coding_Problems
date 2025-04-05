import type { Context } from "moleculer";
import type { IResponse } from "../../types";
import { FanMethods } from "../models";
import { FACTS } from "../constants";

export class ChangeFanState {
  static async handler(ctx: Context): Promise<IResponse> {
    try {
      //@ts-ignore
      const { deviceId, FanState } = ctx.params;
      const updatedFan = await FanMethods.updateSpeed(deviceId, FanState);
      if (!updatedFan) {
        return { success: false, error: "Fan not found" };
      }
      console.log("[ChangeFanState] Context.Meta", ctx.meta)
      ctx.broker.sendToChannel("p2.facts.state.changed", {
        facts: [FACTS.FAN_STATE],
      });
      return { success: true, data: updatedFan };
    } catch (err) {
      console.error("[ChangeFanSpeed] Error:", err);
      return { success: false, error: err?.toString() };
    }
  }
}
