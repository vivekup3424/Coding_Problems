enum PluginTypes {
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

export const NAME = 'kiotp.plugins.general.rulesengine';
export const DISPLAY_NAME = 'Rules Engine';
export const DESCRIPTION = `Rules Engine gives flexibilty to add rules for devices and execute actions based on rules`;
export const VERSION = {
    MAJOR: 1,
    MINOR: 0,
    PATCH: 0
};
export const TYPE = PluginTypes.GENERAL_PLUGIN;

export const CATEGORY = ["general"];

export const PLUGIN_CATEGORY = ["rules_engine"]

export const IMAGES = {
    service: '816687511673.dkr.ecr.ap-south-1.amazonaws.com/keus-iot-platform/gateway-node-manager:latest'
};