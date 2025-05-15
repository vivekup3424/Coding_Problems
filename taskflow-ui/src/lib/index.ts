import type { KeusRealtimeCommunication } from '@keus-automation/kiotp-realtime-js-web';
import axios from "axios";
import RealtimeConnector from './realtime-connector';

// const NATS_CONFIG = {
//     host: `${window.location.protocol.includes("https")? 'wss':'ws'}://localhost`,
//     port: 9767,
//     token: "keus-iot-platform"
// } as const;

// export const realtimeInstance = new KeusRealtimeCommunication(NATS_CONFIG);

export const getSiteId = async () => {
    const nodeConfigRes = await axios.get("http://localhost:3000/keus/v1/node_configuration/GetNodeConfig")
    const siteId = nodeConfigRes.data?.nodeConfig?.siteInfo?.siteId
    // console.log("siteid",siteId)
    if (!siteId) {
        throw new Error("Failed to get siteId")
    }
    return siteId 
}


export const init = async () => {
    // console.log("Initializing realtime instance")
    let connection = await RealtimeConnector.start();
    if (!connection) {
        throw new Error("Failed to connect to realtime server")
    }
    // console.log("Connected to realtime server") 
}