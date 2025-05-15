import type { DataMetaMessage, EventTypeMessage, TaskflowIdMessage } from '$lib/types/realtimeData';
export declare function makeCopy(obj: Object): Promise<any>;
export declare const truncateText: (text: string, maxLength?: number) => string;
export declare const copyToClipBoard: (text: string) => void;
export declare const isEventTypeMessage: (event: any) => event is EventTypeMessage;
export declare const isTaskflowIdMessage: (event: any) => event is TaskflowIdMessage;
export declare const isDataMetaMessage: (event: any) => event is DataMetaMessage;
export declare const handleEventData: (eventData: any) => void;
