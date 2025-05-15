import { taskflowActions, taskflowsMap } from '$lib/stores/taskflow';
import type { DataMetaMessage, EventTypeMessage, TaskflowIdMessage } from '$lib/types/realtimeData';
import { StageStatus, TaskStatus, type Taskflow } from '$lib/types/taskflow';
import { alertStore } from '$lib/utils/alertStore';
import { get } from 'svelte/store';


export async function makeCopy(obj:Object){
    return await JSON.parse(JSON.stringify(obj));
}

export const truncateText = (text: string, maxLength: number = 15) => {
    if (!text) return '';
    if (text.length <= maxLength) {
        return text;
    }
    return text.substring(0, maxLength - 3) + '...';
}

export const copyToClipBoard = (text: string) => {
    const textArea = document.createElement("textarea");
    textArea.value = text;
    textArea.style.position = "fixed";
    textArea.style.zIndex = '-1';
    textArea.style.top = "0";
    textArea.style.left = "0px";
    document.body.appendChild(textArea);
    textArea.focus();
    textArea.select();
    try {
        document.execCommand('copy')
    } catch (err) {
        console.error('Unable to copy to clipboard', err)
    }
    document.body.removeChild(textArea)
};

export const isEventTypeMessage = (event: any): event is EventTypeMessage => {
    return event && typeof event === 'object' && 'eventType' in event;
}

export const isTaskflowIdMessage = (event: any): event is TaskflowIdMessage => {
    return event && typeof event === 'object' && 'taskflowId' in event && !('eventType' in event);
}

export const isDataMetaMessage = (event: any): event is DataMetaMessage => {
    return event && typeof event === 'object' && '__data' in event && '__meta' in event;
}

export const handleEventData = (eventData: any) => {
    // console.log("Received event data:", eventData);

    if(eventData?.eventType == "TASKFLOW"){
        const taskflow = eventData.data.taskflowObject;
        console.log("taskflow from event---",taskflow)
        const taskflowId = taskflow.taskflowId;
        const findTaskflow = get(taskflowsMap).get(taskflowId);
        if(!findTaskflow){
            taskflowActions.addTaskflow(taskflow)
        }
        else taskflowActions.updateTaskflow(taskflow)
    }
    else if(eventData?.eventType == "STAGE"){
        const taskflow = eventData.data.taskflowObject;
        // console.log("taskflow from event---",taskflow)
        const stageId = eventData.data.stageId;
        const stageStatus = Object.values(taskflow.stages).find((s: any) => s.stageId == stageId)?.status || StageStatus.WAITING;
        const taskflowId = taskflow.taskflowId;
        const findTaskflow = get(taskflowsMap).get(taskflowId);
        if(!findTaskflow){
            taskflowActions.addTaskflow(taskflow)
        }
        else taskflowActions.updateStage(taskflow,stageId,stageStatus)
    }
    else if(eventData?.eventType == "TASK"){
        const taskflow:Taskflow = eventData.data.taskflowObject;
        // console.log("taskflow from event---",taskflow)
        const taskId = eventData.data.taskId;
        const taskStatus = Object.values(taskflow.stages).flatMap(stage => Object.values(stage.tasks)).find(task => task.id === taskId)?.status || TaskStatus.WAITING;
        const findTaskflow = get(taskflowsMap).get(taskflow.taskflowId);
        if(!findTaskflow){
            taskflowActions.addTaskflow(taskflow)
        }
        else taskflowActions.updateTask(taskflow,taskId,taskStatus)
    }
}