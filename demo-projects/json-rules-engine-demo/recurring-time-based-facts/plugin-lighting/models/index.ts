import { Schema, model, Document } from "mongoose";

interface Light extends Document {
    deviceId: string;
    LightState: string;
    LightBrightness: string;
    LightColor: string;
}

const LightSchema = new Schema<Light>({
    deviceId: { type: String, required: true },
    LightState: { type: String, required: true },
    LightBrightness: { type: String, required: true },
    LightColor: { type: String, required: true },
});

const LightModel = model<Light>("Light", LightSchema);

export class LightMethods {
 static async insertDefaultLights() {
        try {
            const lightCount = await LightModel.countDocuments();
            if (lightCount === 0) {
                console.info("[LightMethods] No lights found, inserting default lights.");
                const defaultLights = [
                    { deviceId: "Light-L1", LightState: "on", LightBrightness: "50", LightColor: "white" },
                    { deviceId: "Light-L2", LightState: "off", LightBrightness: "30", LightColor: "yellow" },
                    { deviceId: "Light-L3", LightState: "on", LightBrightness: "70", LightColor: "blue" },
                    { deviceId: "Light-L4", LightState: "off", LightBrightness: "20", LightColor: "red" },
                ];
                await LightModel.insertMany(defaultLights);
                console.info("[LightMethods] Default lights inserted successfully.");
            }
        } catch (error) {
            console.error("[LightMethods] Error inserting default lights:", error);
        }
    } 
  static async updateColor(deviceId: string, color: string) {
    try {
      const light = await LightModel.findOne({ deviceId });

      if (!light) {
        console.info("[LightMethods] Light not found for device:", deviceId);
        return { success: false, error: "Light not found" };
      }

      console.info("[LightMethods] Updating LightColor for:", deviceId);
      light.LightColor = color;
      await light.save();

      return { success: true, data: light.toObject() };
    } catch (error) {
      console.error("[LightMethods] Error updating LightColor:", error);
      return { success: false, error: error};
    }
  }

  static async updateState(deviceId: string, state: string) {
    try {
      const light = await LightModel.findOne({ deviceId });

      if (!light) {
        console.info("[LightMethods] Light not found for device:", deviceId);
        return { success: false, error: "Light not found" };
      }

      console.info("[LightMethods] Updating LightState for:", deviceId);
      light.LightState = state;
      await light.save();

      return { success: true, data: light.toObject() };
    } catch (error) {
      console.error("[LightMethods] Error updating LightState:", error);
      return { success: false, error: error};
    }
  }

  static async updateBrightness(deviceId: string, brightness: string) {
    try {
      const light = await LightModel.findOne({ deviceId });

      if (!light) {
        console.info("[LightMethods] Light not found for device:", deviceId);
        return { success: false, error: "Light not found" };
      }

      console.info("[LightMethods] Updating LightBrightness for:", deviceId);
      light.LightBrightness = brightness;
      await light.save();

      return { success: true, data: light.toObject() };
    } catch (error) {
      console.error("[LightMethods] Error updating LightBrightness:", error);
      return { success: false, error: error};
    }
  }

  static async getColor(deviceId: string) {
    try {
      const light = await LightModel.findOne({ deviceId });

      if (!light) {
        console.info("[LightMethods] Light not found for device:", deviceId);
        return { success: false, error: "Light not found" };
      }

      console.info("[LightMethods] Retrieving LightColor for:", deviceId);
      return { success: true, data: { LightColor: light.LightColor } };
    } catch (error) {
      console.error("[LightMethods] Error retrieving LightColor:", error);
      return { success: false, error: error};
    }
  }

  static async getState(deviceId: string) {
    try {
      const light = await LightModel.findOne({ deviceId });

      if (!light) {
        console.info("[LightMethods] Light not found for device:", deviceId);
        return { success: false, error: "Light not found" };
      }

      console.info("[LightMethods] Retrieving LightState for:", deviceId);
      return { success: true, data: { LightState: light.LightState } };
    } catch (error) {
      console.error("[LightMethods] Error retrieving LightState:", error);
      return { success: false, error: error};
    }
  }

  // Get Light Brightness
  static async getBrightness(deviceId: string) {
    try {
      const light = await LightModel.findOne({ deviceId });

      if (!light) {
        console.info("[LightMethods] Light not found for device:", deviceId);
        return { success: false, error: "Light not found" };
      }

      console.info("[LightMethods] Retrieving LightBrightness for:", deviceId);
      return { success: true, data: { LightBrightness: light.LightBrightness } };
    } catch (error) {
      console.error("[LightMethods] Error retrieving LightBrightness:", error);
      return { success: false, error: error};
    }
  }
}

