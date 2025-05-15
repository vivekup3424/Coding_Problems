import { getSiteId } from '$lib';
import { NatsConstants } from '$lib/api/config';
import { liveEventStore, nodeConfig } from '$lib/stores';
import { handleEventData } from '$lib/utils';
import type { KeusRealtimeCommunication as IKeusRealtimeCommunication } from '@keus-automation/kiotp-realtime-js-web';
import { get } from 'svelte/store';
import { alertStore } from '$lib/utils/alertStore';
import { browser } from '$app/environment';


export var KeusRealtimeCommunication: any = null;
export var ConnectionEvents: any = null;
var callId = ``;

type CallerRequest<Data = any> = {
	serviceName: string;
	versionNo: string;
	actionName: string;
	actionData?: Data;
	timeout?: number;
	retries?: number;
};

type CallerResponse<Data = any> = {
	actionResponseData: Data;
	success: boolean;
};

class RealtimeConnector {
	static realtimeInst: IKeusRealtimeCommunication;
	static attemptedReconnection = false;
	static siteId: string;
    static isConnected = false;

	static createRealtimeInstance = (
		host: string = NatsConstants.host,
		port: number = NatsConstants.port,
		token: string = NatsConstants.token
	) => {
		console.log('Creating new realtime instance:', host);

		this.realtimeInst = new KeusRealtimeCommunication({
			host: `${window.location.protocol.includes("https") ? 'wss' : 'ws'}://${host}`,
			port: port,
			token: token,
			reconnection: {
				maxAttempts: -1
			},
			timeout: 5000
		});


		this.realtimeInst.addListener(ConnectionEvents.CONNECTED, () => {
			console.log('Realtime connection established');
            this.isConnected = true;
            alertStore.show('Connected to realtime server', 'success');
		});
        
		this.realtimeInst.addListener(ConnectionEvents.RECONNECTING, () => {
			console.log('Realtime reconnecting...');
			this.attemptedReconnection = true;
            this.isConnected = false;
            alertStore.show('Reconnecting to realtime server...', 'warning');
		});
        
        this.realtimeInst.addListener(ConnectionEvents.DISCONNECTED, () => {
            console.log('Realtime disconnected');
            this.isConnected = false;
            alertStore.show('Disconnected from realtime server', 'error');
        });
	};

	static async start(createInstance: boolean = true, siteId?: string) {
		console.log("rtc", KeusRealtimeCommunication)
		if (!KeusRealtimeCommunication) {
			//@ts-ignore
			KeusRealtimeCommunication = window.KeusRealtimeCommunication;
		}
		if (!ConnectionEvents) {
			//@ts-ignore
			ConnectionEvents = window.ConnectionEvents;
		}

		// console.log("a rtc", window.KeusRealtimeCommunication)

		if (createInstance) this.createRealtimeInstance();
		if(!this.siteId) this.siteId = await getSiteId();
		callId = `${this.siteId}-KIOTP`;

		if (!callId) {
			console.error('Unable to get site ID - failed to start realtime connector');
			return false;
		}
        
		console.log('Connecting to realtime server...');
		const connected = await this.realtimeInst.connect();
		console.log('Realtime connector connected:', connected);
        
		if (!connected) {
			alertStore.show('Failed to connect to realtime server', 'error');
			return false;
		}
        
		this.isConnected = true;
		alertStore.show('Connected to realtime server', 'success');
		this.startLiveEvents();

		return true;
	}

	// static startLiveEvents = async () => {
	// 	if (!this.realtimeInst.connection) {
	// 		console.error('No realtime connection available for event subscription');
	// 		return;
	// 	}
        
	// 	console.log("STARTING LIVE EVENTS for site ID:", this.siteId);

	// 	try {
	// 		// Subscribe to all events for this site
	// 		await RealtimeConnector.realtimeInst.stringListenToEvents(
	// 			`${this.siteId}.>`,
	// 			async(data: string) => {
	// 				try {
	// 					const parsedData = JSON.parse(data);
	// 					console.log("Live event received:", parsedData);
	// 					handleEventData(parsedData);
	// 				} catch (error:any) {
	// 					console.error("Error processing event:", error);
	// 				}
	// 			}
	// 		);
			
	// 		console.log('Successfully subscribed to live events');
	// 		alertStore.show('Listening for taskflow events', 'info');
	// 	} catch (error) {
	// 		console.error("Failed to subscribe to events:", error);
	// 		alertStore.show('Failed to subscribe to events', 'error');
	// 	}
	// };
	static startLiveEvents = async () => {
		if (!this.realtimeInst.connection) {
			console.error('No realtime connection available');
			return false;
		}
		
		console.log("STARTING LIVE EVENTS", this.siteId);
	
		try {
			// Subscribe to all events for this site
			await RealtimeConnector.realtimeInst.stringListenToEvents(
				`${this.siteId}.>`,
				async(data: string) => {
					try {
						const parsedData = JSON.parse(data);
						// console.log("Live event received:", parsedData);
						handleEventData(parsedData);
					} catch (error) {
						console.error("Error processing event:", error);
					}
				}
			);
			
			console.log('Successfully subscribed to live events');
			return true;
		} catch (error) {
			console.error("Failed to subscribe to events:", error);
			return false;
		}
	};
	static async getNodeConfig() {
		let nodeConfigRes = await this.Call<{}, { success: boolean; nodeConfig: any }>({
			serviceName: 'node_configuration',
			versionNo: 'v1',
			actionName: 'GetNodeConfig'
		});

		console.log("Node config response:", nodeConfigRes);

		if (nodeConfigRes?.success) nodeConfig.set(nodeConfigRes?.nodeConfig);
	}

	static async Call<Req, Res>(caller: CallerRequest) {
		if (!this.isConnected) {
			console.warn('Attempting to call RPC while disconnected');
			await this.start();
		}
        
		let resp: Res | null = null;
		// console.log("Calling RPC:", callId, caller);
        
		try {
			let callerRes = await this.realtimeInst.jsonCallRPC<CallerRequest<Req>, CallerResponse<Res>>(
				`${callId}`,
				{
					serviceName: caller.serviceName,
					versionNo: caller.versionNo,
					actionName: caller.actionName,
					actionData: caller.actionData || {},
					timeout: caller.timeout || 30000,
					retries: caller.retries || 1
				}
			);

			// console.log("RPC response:", callerRes);

			if (
				callerRes.success &&
				callerRes.data &&
				callerRes.data.success &&
				callerRes.data.actionResponseData
			) {
				resp = callerRes.data.actionResponseData;
			}
		} catch (error) {
			console.error("RPC call failed:", error);
			alertStore.show(`RPC call to ${caller.serviceName}.${caller.actionName} failed`, 'error');
			throw error;
		}

		return resp;
	}
}

export default RealtimeConnector;