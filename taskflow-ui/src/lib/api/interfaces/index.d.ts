import type { ITask } from "$lib/types/taskflow";
export declare namespace TaskflowApiRequest {
    interface ExecuteTaskflow {
        options?: object;
        stages: {
            name: string;
            tasks: ITask[];
        }[];
    }
}
