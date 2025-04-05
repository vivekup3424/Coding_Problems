
export enum FACTS {
  LIGHT_STATE = "light-state",
  LIGHT_BRIGHTNESS = "light-brightness",
  LIGHT_COLOR = "light-color",
}

export enum EVENTS {
  TRIGGER_Light_STATE_CHANGE = "p2.trigger-Light-state-change",
  TRIGGER_Light_BRIGHTNESS_CHANGE = "p2.trigger-Light-brightness-change",
  TRIGGER_Light_COLOR_CHANGE = "p2.trigger-Light-color-change",
}

export enum Triggers {
  POWER_STATE = "p2.light-power-state",
  BRIGHTNESS = "p2.light-brightness-change",
  COLOR = "p2.light-color-change",
}

export enum POWER {
  ON = "on",
  OFF = "off",
}

export enum BRIGHTNESS {
  LOW = "low",
  MEDIUM = "medium",
  HIGH = "high",
}

export enum COLORS {
  RED = "red",
  GREEN = "green",
  BLUE = "blue",
}

export const FACTS_AND_TRIGGERS = {
  TRIGGERS: [
    {
      displayName: "Change Light Power State",
      eventName: EVENTS.TRIGGER_Light_STATE_CHANGE, // Event Name
      executionStrategy: "durable", // 'durable' or 'fireAndForget'
      params: {
        deviceId: "", // Define device ID here
        powerState: POWER, // for changing Light_STATE
      },
    },
    {
      displayName: "Change Light Brightness",
      eventName: EVENTS.TRIGGER_Light_BRIGHTNESS_CHANGE, // Event Name
      executionStrategy: "durable", // 'durable' or 'fireAndForget'
      params: {
        deviceId: "", // Define device ID here
        brightnessLevel: BRIGHTNESS, // used for changing BRIGHTNESS
      },
    },
    {
      displayName: "Change Light Color",
      eventName: EVENTS.TRIGGER_Light_COLOR_CHANGE, // Event Name
      executionStrategy: "durable", // 'durable' or 'fireAndForget'
      params: {
        deviceId: "", // Define device ID here
        colorName: COLORS, // used for changing Light_COLOR
      },
    },
  ],
  FACTS: [
    {
      factName: FACTS.LIGHT_STATE,
      factValues: [POWER.ON, POWER.OFF], // Define power states
    },
    {
      factName: FACTS.LIGHT_BRIGHTNESS,
      factValues: [BRIGHTNESS.LOW, BRIGHTNESS.MEDIUM, BRIGHTNESS.HIGH], // Define brightness levels
    },
    {
      factName: FACTS.LIGHT_COLOR,
      factValues: [COLORS.RED, COLORS.GREEN, COLORS.BLUE], // Define available colors
    },
  ],
};