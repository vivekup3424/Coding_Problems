import type { Context } from "moleculer";
import type { IResponse } from "../../types";
import { LightMethods} from "../models";
import { FACTS } from "../constants";

export class ChangeLightColor {
  static async handler(ctx: Context): Promise<IResponse> {
    try {
      //@ts-ignore
      const { deviceId, LightColor } = ctx.params;
      const updatedLight = await LightMethods.updateColor(deviceId, LightColor);
      if (!updatedLight) {
        return { success: false, error: "Fan not found" };
      }
      console.log("[ChangeLightColor] Context.Meta", ctx.meta)
      ctx.broker.sendToChannel("p2.facts.state.changed", {
        facts: [FACTS.LIGHT_COLOR],
      },{ctx});
      return { success: true, data: updatedLight};
    } catch (err) {
      console.error("[ChangeLightColor] Error:", err);
      return { success: false, error: err?.toString() };
    }
  }
}


