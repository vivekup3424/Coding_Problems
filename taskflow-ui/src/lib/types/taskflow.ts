export interface ITask {
  name: string;
  params?: object;
  type: string;
  taskDetails?: {
    serviceId?: string;
    actionName?: string;
    channelName?: string;
  },
  options?: object
}

export interface Task extends ITask {
  id: string;
  status: TaskStatus;
  stageId: string;
  nestedTaskflowId?: string;
  nestedTaskflows?: string[];
  response?: any;
  attempt?: number
}

export interface IStage {
  name: string,
  tasks: Task[]
}

export interface Stage extends IStage {
  id: string;
  status: StageStatus;
}

export interface ITaskflow {
  options?: object,
  stages: Stage[]
}

export interface Taskflow extends ITaskflow {
  _id: string;
  taskflowId: string;
  name: string;
  status: TaskflowStatus;
  createdAt: number;
  parentTaskflowDetails: any;
  context: any;
  retryAttempt: number
}

export enum TaskStatus {
  WAITING = "WAITING",
  QUEUED = "QUEUED",
  RUNNING = "RUNNING",
  SUCCESS = "SUCCESS",
  FAILED = "FAILED",
}

export enum StageStatus {
  WAITING = "WAITING",
  RUNNING = "RUNNING",
  COMPLETED = "COMPLETED",
  PARTIAL_COMPLETED = "PARTIAL_COMPLETED",
  FAILED = "FAILED"
}

export enum TaskflowStatus {
  WAITING = "WAITING",
  RUNNING = "RUNNING",
  COMPLETED = "COMPLETED",
  CANCELLED = "CANCELLED",
  PARTIAL_COMPLETED = "PARTIAL_COMPLETED",
  FAILED = "FAILED"
}

// export interface Taskflow {
//     taskflowId: string;
//     status: TaskflowStatus;
//     createdAt: number;
//     stages?: Array<{
//         id: string;
//         name: string;
//         status: StageStatus;
//         tasks: Array<{
//             id: string;
//             name: string;
//             status: TaskStatus;
//         }>;
//     }>;
// }


