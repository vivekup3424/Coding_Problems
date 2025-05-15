<script lang="ts">
    import { activeTaskflow, taskflowsMap } from "$lib/stores/taskflow";
	import { type Taskflow, TaskflowStatus } from "$lib/types/taskflow";
	
	export let taskflow: Taskflow;
	
	function getStatusColor(status: TaskflowStatus): string {
		if (status === TaskflowStatus.COMPLETED) return 'bg-green-500';
		if (status === TaskflowStatus.RUNNING) return 'bg-yellow-500';
		if (status === TaskflowStatus.CANCELLED) return 'bg-red-500';
		if (status === TaskflowStatus.PARTIAL_COMPLETED) return 'bg-orange-500';
		if (status === TaskflowStatus.FAILED) return 'bg-red-500';
		return 'bg-gray-500';
	}
	
	$: stageCount = Object.values($taskflowsMap.get(taskflow.taskflowId)?.stages || []).length;
	$: taskCount = Object.values($taskflowsMap.get(taskflow.taskflowId)?.stages || [])
    .reduce((count, stage) => count + Object.keys(stage.tasks).length, 0);

</script>
  
<div class="grid grid-cols-4 gap-6 mb-6">
	<div class="bg-white shadow-sm rounded-md p-4">
		<div class="text-sm text-gray-500 mb-1">Status</div>
		<div class="text-2xl font-bold text-gray-800">{$taskflowsMap.get(taskflow.taskflowId)?.status}</div>
		<div class="w-full h-2 {getStatusColor($taskflowsMap.get(taskflow.taskflowId)?.status || TaskflowStatus.WAITING)} rounded-full"></div>
	</div>
	
	<div class="bg-white shadow-sm rounded-md p-4">
		<div class="text-sm text-gray-500 mb-1">Total Stages</div>
		<div class="text-2xl font-bold text-gray-800">{stageCount}</div>
		<div class="h-1 w-24 rounded mt-2 bg-blue-500"></div>
	</div>
	
	<div class="bg-white shadow-sm rounded-md p-4">
		<div class="text-sm text-gray-500 mb-1">Total Tasks</div>
		<div class="text-2xl font-bold text-gray-800">{taskCount}</div>
		<div class="h-1 w-24 rounded mt-2 bg-purple-500"></div>
	</div>

	<div class="bg-white shadow-sm rounded-md p-4">
		<div class="text-sm text-gray-500 mb-1">Retry Attempts</div>
		<div class="text-2xl font-bold text-gray-800">{taskflow.retryAttempt}</div>
		<div class="h-1 w-24 rounded mt-2 bg-orange-500"></div>
	</div>
</div>