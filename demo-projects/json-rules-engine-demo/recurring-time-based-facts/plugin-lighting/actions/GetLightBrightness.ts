import type { Context } from "moleculer";
import type { IResponse } from "../../types";
import { LightMethods} from "../models";
export class GetLightBrightness {
    static async handler(ctx: Context): Promise<IResponse> {
        try {
            //@ts-ignore
            const deviceId = ctx.params?.deviceId;
            if (!deviceId) {
                return {
                    success: false,
                    error: "Missing deviceId",
                };
            }

            const { success, data: lightData } = await LightMethods.getBrightness(deviceId);

            return {
                success,
                data: lightData?.LightBrightness,
            };
        } catch (err) {
            console.error("[GetLightBrightness] Error:", err);
            return {
                success: false,
                error: err?.toString(),
            };
        }
    }
}