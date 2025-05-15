import type { Taskflow, TaskStatus } from '$lib/types/taskflow';
import type { TaskflowApiRequest } from '$lib/api/interfaces';
export declare const taskflowsMap: import("svelte/store").Writable<Map<string, Taskflow>>;
export declare const taskflows: import("svelte/store").Readable<Taskflow[]>;
export declare const activeTaskflow: import("svelte/store").Writable<any>;
export declare const activeTaskflowTab: import("svelte/store").Writable<string>;
export declare const expandedTasks: import("svelte/store").Writable<Map<string, boolean>>;
export declare const expandedStages: import("svelte/store").Writable<Map<string, boolean>>;
export declare const taskflowActions: {
    fetchTaskflows(): Promise<{
        success: boolean;
        error?: undefined;
    } | {
        success: boolean;
        error: unknown;
    }>;
    executeTaskflow(taskflow: TaskflowApiRequest.ExecuteTaskflow): Promise<{
        success: boolean;
        taskflow: any;
        error?: undefined;
    } | {
        success: boolean;
        error: unknown;
        taskflow?: undefined;
    }>;
    updateTaskflowStatus(id: string, status: string): void;
    initializeExpandedStates(taskflow: Taskflow): void;
    toggleTaskExpansion(taskId: string): void;
    toggleStageExpansion(stageId: string): void;
    setActiveTaskflow(taskflow: Taskflow): void;
    setActiveTaskflowTab(tab: string): void;
    addTaskflow(taskflow: Taskflow): void;
    updateTaskflow(taskflow: Taskflow): void;
    updateStage(taskflow: Taskflow, stageId: string, status: string): void;
    updateTask(taskflow: Taskflow, taskId: string, status: TaskStatus): void;
};
