import cron from "node-cron"
export declare enum PluginTypes {
    CORE_PLUGIN = "CORE_PLUGIN",
    DEVICE_PLUGIN = "DEVICE_PLUGIN",
    GENERAL_PLUGIN = "GENERAL_PLUGIN",
    AGGREGATOR_PLUGIN = "AGGREGATOR_PLUGIN"
}
export declare enum ApplianceType {
    CONTENT = "CONTENT",
    AUDIO = "AUDIO",
    VIDEO = "VIDEO",
    DISPLAY = "DISPLAY",
    SYSTEM = "SYSTEM"
}
export declare namespace IPluginConfig {
    interface IPluginConfigData {
        ID: string;
        NAME: string;
        DISPLAY_NAME: string;
        DESCRIPTION: string;
        VERSION: {
            MAJOR: number;
            MINOR: number;
            PATCH: number;
        };
        TYPE: PluginTypes;
        IMAGES: {
            SERVICE: string;
            CONTAINER_CONFIG?: {
                allowHostNetwork: boolean;
            };
        };
        PLUGIN_CATEGORY?: string[];
        CATEGORY?: string[];
    }
    enum TriggerType {
        INT = "int",
        BOOL = "bool",
        STRING = "string"
    }
}
export interface VersionObject {
    MAJOR: number;
    MINOR: number;
    PATCH: number;
}
export interface JobInfo {
    task: cron.ScheduledTask;
    cronExpression: string;
    taskFunction: () => void;
}
export interface IFactsAndTriggers {
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
export const GetVersionStr = function (versionObj: VersionObject) {
    return `${versionObj.MAJOR}.${versionObj.MINOR}.${versionObj.PATCH}`;
}
export namespace IGetFactsTriggerAction {
    export interface Request {
    }

    export interface Response {
        success: boolean;
        data: IFactsAndTriggers;
    }
}
export interface IResponse<Data = any> {
    success: boolean;
    error?: string;
    data?: Data;
}

export const AsyncDelay = function(delay: number) {
    return new Promise(function(resolve) {
        setTimeout(function() {
            resolve({});
        }, delay)
    });
}
export const buildPayload = (customActionData?: Record<string, any>): Record<string, any> => {
    if (!customActionData) return {};
    return Object.fromEntries(customActionData.entries());
  };