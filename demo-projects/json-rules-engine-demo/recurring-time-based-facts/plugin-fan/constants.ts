export enum FACTS {
    FAN_STATE = "fan-power-state",
    SPEED = "fan-speed-change",
    MODE = "fan-mode-change"
}

export enum EVENTS {
    TRIGGER_FAN_STATE_CHANGE = "p2.trigger-fan-state-change",
    TRIGGER_FAN_SPEED_CHANGE = "p2.trigger-fan-speed-change",
    TRIGGER_FAN_MODE_CHANGE = "p2.trigger-fan-mode-change"
}

export enum Triggers {
    POWER_STATE = "p2.fan-power-state",
    SPEED = "p2.fan-speed-change",
    MODE = "p2.fan-mode-change"
}

export enum POWER {
    ON = "on",
    OFF = "off"
}

export enum SPEEDS {
    LOW = "low",
    MEDIUM = "medium",
    HIGH = "high"
}

export enum MODES {
    NORMAL = "normal",
    SLEEP = "sleep",
    TURBO = "turbo"
}
//create an interface for factsandtriggers
interface IFactsAndTriggers {
    TRIGGERS: {
        displayName: string;
        eventName: string;
        executionStrategy: string;
        params: Record<string, any>;
    }[],
    FACTS: {
        factName: string;
        factValues: string[];
    }[]
}

export const FACTS_AND_TRIGGERS:IFactsAndTriggers = {
        "TRIGGERS": [
            {
                displayName: "Change Fan Power State",
                eventName: EVENTS.TRIGGER_FAN_SPEED_CHANGE, //Event Name 
                executionStrategy: 'durable', // 'durable' or 'fireAndForget'
                params: {
                    deviceId: ""
                }
            },
            {
                displayName: "Change Fan Speed",
                eventName: EVENTS.TRIGGER_FAN_SPEED_CHANGE,
                executionStrategy: 'durable',
                params: {
                    deviceId: "",
                    speedLevel: "", //used for changing SPEED
                }
            },
            {
                displayName: "Change Fan Mode",
                eventName: EVENTS.TRIGGER_FAN_MODE_CHANGE,
                executionStrategy: 'durable',
                params: {
                    deviceId: "",
                    modeName: "",
                }
            }
        ],
    
        "FACTS": [
            {
                factName: FACTS.FAN_STATE,
                factValues : [POWER.ON, POWER.OFF],
            },
            {
                factName: FACTS.SPEED,
                factValues : [SPEEDS.LOW, SPEEDS.MEDIUM, SPEEDS.HIGH],
            },
            {
                factName: FACTS.MODE,
                factValues : [MODES.NORMAL, MODES.SLEEP, MODES.TURBO],
            }
        ]
    }

