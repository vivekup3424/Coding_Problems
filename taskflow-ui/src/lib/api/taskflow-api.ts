import { TASKFLOW_SERVICE_NAME, TASKFLOW_SERVICE_VERSION } from '$lib/constants';
import RealtimeConnector from '$lib/realtime-connector';
import type { Taskflow } from '$lib/types/taskflow';
import type { CallerRequest, CallerResponse } from '@keus-automation/kiotp-ui-types';
import type { TaskflowApiRequest } from './interfaces';
import type { ITemplate, Template } from '$lib/types/template';

export interface successInfo {
	success: boolean;
}

class TaskflowApi {
	private static async Caller<ResponseType = any>(name: string, data?: any) {
		let res = await RealtimeConnector.Call<CallerRequest, CallerResponse<ResponseType>>({
			serviceName: TASKFLOW_SERVICE_NAME,
			versionNo: TASKFLOW_SERVICE_VERSION,
			actionName: name,
			actionData: data || {},
		});

		return res;
	}

	static async GetAllTaskflows():Promise<Taskflow[]> {
		try {
			let allTaskflowsRes = await this.Caller("GetAllTaskflowsDetails")
			console.log("allTaskflowsRes---",allTaskflowsRes)
			if(!allTaskflowsRes?.success){
				throw new Error(`API error: ${allTaskflowsRes?.data?.status}`)
			}
			return allTaskflowsRes?.data
		} catch (err) {
			console.error("Failed to get all taskflows", err)
			throw err;
		}
	}

	static async getTaskflowById(taskflowId: string):Promise<Taskflow> {
		try {
			let res = await this.Caller("GetTaskflowDetails",{taskflowId})
			if(!res?.success){
				throw new Error(`API error: ${res?.data?.status}`)
			}
			return res?.data
		} catch (err) {
			console.error("Failed to get taskflow", err)
			throw err;
		}
	}

	static async retryTaskflow(taskflowId: string):Promise<Taskflow> {
		try {
			let res = await this.Caller("RetryTaskflow",{taskflowId})
			if(!res?.success){
				throw new Error(`API error: ${res?.data?.status}`)
			}
			return res?.data
		} catch (err) {
			console.error("Failed to retry taskflow", err)
			throw err;
		}
	}

	static async cancelTaskflow(taskflowId: string):Promise<Taskflow> {
		try {
			let res = await this.Caller("CancelTaskflow",{taskflowId})
			if(!res?.success){
				throw new Error(`API error: ${res?.data?.status}`)
			}
			return res?.data
		} catch (err) {
			console.error("Failed to cancel taskflow", err)
			throw err;
		}
	}

	static async executeTaskflow(taskflow: TaskflowApiRequest.ExecuteTaskflow):Promise<Taskflow> {
		try {
			let res = await this.Caller("Produce",taskflow)
			if(!res?.success){
				throw new Error(`API error: ${res?.data?.status}`)
			}
			return res?.data
		} catch (err) {
			console.error("Failed to execute taskflow", err)
			throw err;
		}
	}																					

	static async getAllTemplates():Promise<Template[]> {
		try {
			let res = await this.Caller("GetAllTemplates")
			if(!res?.success){
				throw new Error(`API error: ${res?.data?.status}`)
			}
			return res?.data
		} catch (err) {
			console.error("Failed to get all templates", err)
			throw err;
		}
	}

	static async createTemplate(template: Omit<ITemplate, 'id' | 'createdAt'>):Promise<Template> {
		try {
			let res = await this.Caller("AddTemplate",{template})
			if(!res?.success){
				throw new Error(`API error: ${res?.data?.status}`)
			}
			return res?.data
		} catch (err) {
			console.error("Failed to create template", err)
			throw err;
		}
	}

	static async executeTemplate(templateId: string):Promise<Taskflow> {
		try {
			let res = await this.Caller("ExecuteTemplate",{templateId})
			if(!res?.success){
				throw new Error(`API error: ${res?.data?.status}`)
			}
			return res?.data
		} catch (err) {
			console.error("Failed to execute template", err)
			throw err;
		}
	}

	static async updateTemplate(template: Partial<Template>): Promise<Template> {
		try {
			let res = await this.Caller("UpdateTemplate", { template });
			if (!res?.success) {
				throw new Error(`API error: ${res?.data?.status}`);
			}
			return res?.data;
		} catch (err) {
			console.error("Failed to update template", err);
			throw err;
		}
	}
	
	static async deleteTemplate(templateId: string): Promise<boolean> {
		try {
			let res = await this.Caller("DeleteTemplate", { templateId });
			if (!res?.success) {
				throw new Error(`API error: ${res?.data?.status}`);
			}
			return true;
		} catch (err) {
			console.error("Failed to delete template", err);
			throw err;
		}
	}
	
	static async CustomCaller<ReqDataType, ResDataType>(
		serviceId: string,
		serviceVersion: string,
		action: string,
		data: any,
		timeout: number = 30000
	) {
		let res = await RealtimeConnector.Call<ReqDataType, ResDataType>({
			serviceName: serviceId,
			actionName: action,
			versionNo: serviceVersion,
			actionData: data,
			timeout: timeout
		});


		return res;
	}
}

export { TaskflowApi };
