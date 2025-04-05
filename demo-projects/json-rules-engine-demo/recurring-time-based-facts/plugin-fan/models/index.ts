import { Schema, model, Document } from "mongoose";

interface Fan extends Document {
    deviceId: string;
    FanState: string;
    FanSpeed: string;
    FanMode: string;
}
const FanSchema = new Schema<Fan>({
    deviceId: { type: String, required: true },
    FanState: { type: String, required: true },
    FanSpeed: { type: String, required: true },
    FanMode: { type: String, required: true },
});

const FanModel = model<Fan>("Fan", FanSchema);

export class FanMethods {
    static async insertDefaultFans() {
        try {
            const fanCount = await FanModel.countDocuments();
            if (fanCount === 0) {
                console.info("[FanMethods] No fans found, inserting default fans.");
                const defaultFans = [
                    { deviceId: "Fan-F1", FanState: "on", FanSpeed: "low", FanMode: "normal" },
                    { deviceId: "Fan-F2", FanState: "off", FanSpeed: "medium", FanMode: "sleep" },
                    { deviceId: "Fan-F3", FanState: "on", FanSpeed: "high", FanMode: "turbo" },
                    { deviceId: "Fan-F4", FanState: "off", FanSpeed: "low", FanMode: "normal" },
                ];
                await FanModel.insertMany(defaultFans);
                console.info("[FanMethods] Default fans inserted successfully.");
            }
        } catch (error) {
            console.error("[FanMethods] Error inserting default fans:", error);
        }
    }
    static async updateState(deviceId: string, state: string) {
        try {
            const fan = await FanModel.findOne({ deviceId });
            if (!fan) return { success: false, error: "Fan not found" };
            
            fan.FanState = state;
            await fan.save();
            return { success: true, data: fan.toObject() };
        } catch (error) {
            console.error("[FanMethods] Error updating FanState:", error);
            return { success: false, error };
        }
    }

    static async updateSpeed(deviceId: string, speed: string) {
        try {
            const fan = await FanModel.findOne({ deviceId });
            if (!fan) return { success: false, error: "Fan not found" };
            
            fan.FanSpeed = speed;
            await fan.save();
            return { success: true, data: fan.toObject() };
        } catch (error) {
            console.error("[FanMethods] Error updating FanSpeed:", error);
            return { success: false, error };
        }
    }

    static async updateMode(deviceId: string, mode: string) {
        try {
            const fan = await FanModel.findOne({ deviceId });
            if (!fan) return { success: false, error: "Fan not found" };
            
            fan.FanMode = mode;
            await fan.save();
            return { success: true, data: fan.toObject() };
        } catch (error) {
            console.error("[FanMethods] Error updating FanMode:", error);
            return { success: false, error };
        }
    }

    static async getState(deviceId: string) {
        try {
            const fan = await FanModel.findOne({ deviceId });
            if (!fan) return { success: false, error: "Fan not found" };
            
            return { success: true, data: { fanState: fan.FanState } };
        } catch (error) {
            console.error("[FanMethods] Error retrieving FanState:", error);
            return { success: false, error };
        }
    }

    static async getSpeed(deviceId: string) {
        try {
            const fan = await FanModel.findOne({ deviceId });
            if (!fan) return { success: false, error: "Fan not found" };
            
            return { success: true, data: { fanSpeed: fan.FanSpeed } };
        } catch (error) {
            console.error("[FanMethods] Error retrieving FanSpeed:", error);
            return { success: false, error };
        }
    }

    static async getMode(deviceId: string) {
        try {
            const fan = await FanModel.findOne({ deviceId });
            if (!fan) return { success: false, error: "Fan not found" };
            
            return { success: true, data: { fanMode: fan.FanMode } };
        } catch (error) {
            console.error("[FanMethods] Error retrieving FanMode:", error);
            return { success: false, error };
        }
    }
}
