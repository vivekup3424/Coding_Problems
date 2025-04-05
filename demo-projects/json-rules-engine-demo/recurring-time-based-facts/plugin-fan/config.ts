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

export const NAME = 'kiotp.plugins.general.fan';
export const DISPLAY_NAME = 'FAN SERVICE';
export const DESCRIPTION = `Fan Service is responsible for starting fans, scheduling fan automations and listening for new events regarding fan movement`;
export const VERSION = {
    MAJOR: 1,
    MINOR: 0,
    PATCH: 0
};
export const TYPE = PluginTypes.GENERAL_PLUGIN;

export const CATEGORY = ["general"];

export const PLUGIN_CATEGORY = ["fan_service"]

export const IMAGES = {
    service: '816687511673.dkr.ecr.ap-south-1.amazonaws.com/keus-iot-platform/gateway-node-manager:latest'
};
