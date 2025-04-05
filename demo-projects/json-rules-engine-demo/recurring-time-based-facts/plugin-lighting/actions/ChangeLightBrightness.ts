import type { Context } from "moleculer";
import type { IResponse } from "../../types";
import { LightMethods} from "../models";
import { FACTS } from "../constants";

export class ChangeLightBrightness {
  static async handler(ctx: Context): Promise<IResponse> {
    try {
      //@ts-ignore
      const { deviceId, LightBrightness } = ctx.params;
      const updatedLight = await LightMethods.updateBrightness(deviceId, LightBrightness);
      if (!updatedLight) {
        return { success: false, error: "Fan not found" };
      }
      ctx.broker.sendToChannel("p2.facts.state.changed", {
        facts: [FACTS.LIGHT_BRIGHTNESS],
      });
      return { success: true, data: updatedLight};
    } catch (err) {
      console.error("[ChangeLightBrightness] Error:", err);
      return { success: false, error: err?.toString() };
    }
  }
}


