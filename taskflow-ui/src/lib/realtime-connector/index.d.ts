import type { KeusRealtimeCommunication as IKeusRealtimeCommunication } from '@keus-automation/kiotp-realtime-js-web';
export declare var KeusRealtimeCommunication: any;
export declare var ConnectionEvents: any;
type CallerRequest<Data = any> = {
    serviceName: string;
    versionNo: string;
    actionName: string;
    actionData?: Data;
    timeout?: number;
    retries?: number;
};
declare class RealtimeConnector {
    static realtimeInst: IKeusRealtimeCommunication;
    static attemptedReconnection: boolean;
    static siteId: string;
    static isConnected: boolean;
    static createRealtimeInstance: (host?: string, port?: number, token?: string) => void;
    static start(createInstance?: boolean, siteId?: string): Promise<boolean>;
    static startLiveEvents: () => Promise<boolean>;
    static getNodeConfig(): Promise<void>;
    static Call<Req, Res>(caller: CallerRequest): Promise<Res | null>;
}
export default RealtimeConnector;
