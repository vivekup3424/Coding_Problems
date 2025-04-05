import type { Context } from "moleculer";
import type { IResponse } from "../../types";
import { FACTS, POWER } from "../constants";
import { FanMethods} from "../models";
export class GetFanMode {
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

            const { success, data: fanData } = await FanMethods.getMode(deviceId);

            return {
                success,
                data: fanData?.fanMode,
            };
        } catch (err) {
            console.error("[GetFanMode] Error:", err);
            return {
                success: false,
                error: err?.toString(),
            };
        }
    }
}
