export type EventType = 'TASK' | 'STAGE' | 'TASKFLOW';
export interface TaskflowEvent {
    eventType: EventType;
    data: {
        taskflow: {
            taskflowId: string;
            status: string;
            retryAttempt: number;
            stages: Array<{
                id: string;
                name: string;
                status: string;
                tasks: Array<{
                    id: string;
                    name: string;
                    status: string;
                    attempt: number;
                    response?: any;
                    nestedTaskFlows: any[];
                }>;
            }>;
        };
    };
}
export interface EventTypeMessage {
    eventType: string;
    data: any;
}
export interface TaskflowIdMessage {
    taskflowId: string;
}
export interface DataMetaMessage {
    __data: object;
    __meta: object;
}
export declare const isTaskflowEvent: (event: any) => event is TaskflowEvent;
