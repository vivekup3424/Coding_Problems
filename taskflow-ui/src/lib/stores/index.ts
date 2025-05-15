import { writable, type Writable } from "svelte/store";
import { taskflowActions } from "./taskflow";
import { templateActions } from "./template";

export const nodeConfig: Writable<any> = writable(null);
export const liveEventStore: Writable<any> = writable(null);
export const selectedTaskflow: Writable<any> = writable(null);


export const refreshData = async () => {
	await taskflowActions.fetchTaskflows();
	await templateActions.fetchTemplates()
}
