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

export const isTaskflowEvent = (event: any): event is TaskflowEvent => {
    return event && 
           typeof event === 'object' && 
           'eventType' in event &&
           'data' in event &&
           event.data && 
           typeof event.data === 'object' &&
           'taskflow' in event.data &&
           event.data.taskflow && 
           'taskflowId' in event.data.taskflow;
};