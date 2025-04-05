import type { Context } from "moleculer";
import type { IResponse } from "../../types";
import { LightMethods} from "../models";
export class GetLightColor {
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

            const { success, data: lightData } = await LightMethods.getColor(deviceId);

            return {
                success,
                data: lightData?.LightColor,
            };
        } catch (err) {
            console.error("[GetLightColor] Error:", err);
            return {
                success: false,
                error: err?.toString(),
            };
        }
    }
}