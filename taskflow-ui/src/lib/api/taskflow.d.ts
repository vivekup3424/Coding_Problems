import type { Taskflow } from '$lib/types/taskflow';
import type { TaskflowApiRequest } from './interfaces';
export declare class TaskflowApiCaller {
    static getAllTaskflows(): Promise<Taskflow[]>;
    static getTaskflowById(taskflowId: string): Promise<Taskflow>;
    static executeTaskflow(taskflow: TaskflowApiRequest.ExecuteTaskflow): Promise<Taskflow>;
}
