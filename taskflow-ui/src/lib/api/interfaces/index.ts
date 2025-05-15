import type { IStage, ITask } from "$lib/types/taskflow";


export namespace TaskflowApiRequest {
	export interface ExecuteTaskflow {
		options?: object,
		stages: {
			name: string,
			tasks: ITask[]
		}[],
		
	}
}
  
  