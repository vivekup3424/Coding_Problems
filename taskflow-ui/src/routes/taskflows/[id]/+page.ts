import { TaskflowApi } from '$lib/api/taskflow-api';
import { TaskflowApiCaller } from '$lib/api/taskflow.js';
import { activeTaskflow, taskflows, taskflowsMap } from '$lib/stores/taskflow';
import { get } from 'svelte/store';

// export const ssr  = false
export const load = async ({ params, fetch }) => {
	const { id } = params;
	
	try {
		
		const taskflow = await TaskflowApi.getTaskflowById(id)
		console.log("taskflow---",taskflow)
		activeTaskflow.set(taskflow)
		
	  return {
		taskflow
	  };
	} catch (error:any) {
	  return {
		status: 500,
		error: new Error(`Failed to load taskflow: ${error.message}`)
	  };
	}
  };