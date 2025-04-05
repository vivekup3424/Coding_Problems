import type { Context } from "moleculer";
import type { IResponse } from "../../types";
import { FanMethods} from "../models";
export class GetFanSpeed {
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

            const { success, data: fanData } = await FanMethods.getSpeed(deviceId);

            return {
                success,
                data: fanData?.fanSpeed,
            };
        } catch (err) {
            console.error("[GetFanSpeed] Error:", err);
            return {
                success: false,
                error: err?.toString(),
            };
        }
    }
}
