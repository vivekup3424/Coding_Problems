import type { Context } from "moleculer";
import type { IResponse } from "../../types";
import { FanMethods } from "../models";
import { FACTS } from "../constants";

export class ChangeFanSpeed {
  static async handler(ctx: Context): Promise<IResponse> {
    try {
      //@ts-ignore
      const { deviceId, FanSpeed } = ctx.params;
      const updatedFan = await FanMethods.updateSpeed(deviceId, FanSpeed);
      if (!updatedFan) {
        return { success: false, error: "Fan not found" };
      }
      ctx.broker.sendToChannel("p2.facts.state.changed", {
        facts: [FACTS.SPEED],
      });
      return { success: true, data: updatedFan };
    } catch (err) {
      console.error("[ChangeFanSpeed] Error:", err);
      return { success: false, error: err?.toString() };
    }
  }
}
