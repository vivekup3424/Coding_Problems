import type { Taskflow } from '$lib/types/taskflow';
import type { TaskflowApiRequest } from './interfaces';
import type { ITemplate, Template } from '$lib/types/template';
export interface successInfo {
    success: boolean;
}
declare class TaskflowApi {
    private static Caller;
    static GetAllTaskflows(): Promise<Taskflow[]>;
    static getTaskflowById(taskflowId: string): Promise<Taskflow>;
    static retryTaskflow(taskflowId: string): Promise<Taskflow>;
    static cancelTaskflow(taskflowId: string): Promise<Taskflow>;
    static executeTaskflow(taskflow: TaskflowApiRequest.ExecuteTaskflow): Promise<Taskflow>;
    static getAllTemplates(): Promise<Template[]>;
    static createTemplate(template: Omit<ITemplate, 'id' | 'createdAt'>): Promise<Template>;
    static executeTemplate(templateId: string): Promise<Taskflow>;
    static updateTemplate(template: Partial<Template>): Promise<Template>;
    static deleteTemplate(templateId: string): Promise<boolean>;
    static CustomCaller<ReqDataType, ResDataType>(serviceId: string, serviceVersion: string, action: string, data: any, timeout?: number): Promise<any>;
}
export { TaskflowApi };
