<script lang="ts">
	import type { Taskflow } from "$lib/types/taskflow";
	import { onMount } from 'svelte';
	import { TaskStatus } from '$lib/types/taskflow';
	
	export let taskflow: Taskflow;
	
	// Generate simulated logs based on actual taskflow data
	function generateLogs(taskflow: Taskflow) {
		let logs = [];
		const baseTime = new Date(Number(taskflow.createdAt));
		let timeOffset = 0;
		
		// Taskflow started log
		logs.push({
			time: formatTime(baseTime),
			event: 'TASKFLOW',
			component: taskflow.name || 'Taskflow',
			status: 'STARTED',
			level: 0
		});
		
		// Generate logs for each stage and task
		taskflow.stages.forEach((stage, stageIndex) => {
			timeOffset += 2 * 60 * 1000; // 2 minutes after previous event
			const stageTime = new Date(Number(taskflow.createdAt) + timeOffset);
			
			logs.push({
				time: formatTime(stageTime),
				event: 'STAGE',
				component: stage.name,
				status: stage.status,
				level: 0
			});
			
			stage.tasks.forEach((task, taskIndex) => {
				timeOffset += 1 * 60 * 1000; // 1 minute after previous event
				const taskTime = new Date(Number(taskflow.createdAt) + timeOffset);
				
				logs.push({
					time: formatTime(taskTime),
					event: 'TASK',
					component: task.name,
					status: task.status,
					level: task.nestedTaskflowId ? 1 : 0 // Treat tasks with nested taskflows as level 1
				});
				
				if (task.nestedTaskflowId) {
					timeOffset += 30 * 1000; // 30 seconds after previous event
					const nestedTime = new Date(Number(taskflow.createdAt) + timeOffset);
					
					logs.push({
						time: formatTime(nestedTime),
						event: 'NESTED L1',
						component: `Nested Taskflow (${task.nestedTaskflowId.substring(0, 8)}...)`,
						status: task.status,
						level: 1
					});
				}
			});
		});
		
		return logs;
	}
	
	function formatTime(date: Date) {
		return date.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit', second: '2-digit' });
	}
	
	$: logs = generateLogs(taskflow);
	
	function getStatusClass(status: TaskStatus): string {
		return status === TaskStatus.SUCCESS ? 'bg-green-100 text-green-800' :
			status === TaskStatus.RUNNING ? 'bg-yellow-100 text-yellow-800' :
			status === TaskStatus.FAILED ? 'bg-red-100 text-red-800' :
			'bg-gray-100 text-gray-800';
	}
</script>
  
<div>
	<div class="mb-4 bg-gray-50 p-3 rounded text-sm text-gray-500">
		These are simulated logs based on the taskflow structure. In a production environment, you would connect to real-time logs from the taskflow execution.
	</div>
  
	<table class="min-w-full divide-y divide-gray-200">
		<thead class="bg-gray-50">
			<tr>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Time</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Event</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Component</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Status</th>
			</tr>
		</thead>
		<tbody class="bg-white divide-y divide-gray-200">
			{#each logs as log}
				<tr class={log.level === 1 ? 'bg-blue-50 bg-opacity-40' : log.level === 2 ? 'bg-purple-50 bg-opacity-40' : ''}>
					<td class="px-6 py-4 whitespace-nowrap text-sm text-gray-500">{log.time}</td>
					<td class="px-6 py-4 whitespace-nowrap text-sm {log.level === 1 ? 'text-blue-700' : log.level === 2 ? 'text-purple-700' : 'text-gray-900'}">{log.event}</td>
					<td class="px-6 py-4 whitespace-nowrap text-sm {log.level === 1 ? 'text-blue-700' : log.level === 2 ? 'text-purple-700' : 'text-gray-900'}">{log.component}</td>
					<td class="px-6 py-4 whitespace-nowrap">
						<span class={`px-2 py-1 rounded-full text-xs ${getStatusClass(log.status)}`}>
							{log.status}
						</span>
					</td>
				</tr>
			{/each}
		</tbody>
	</table>
</div>