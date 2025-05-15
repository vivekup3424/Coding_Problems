<script lang="ts">
	import type { Taskflow, Task } from "$lib/types/taskflow";
	import { expandedTasks, taskflowActions } from '$lib/stores/taskflow';
	import { get } from 'svelte/store';
	import { TaskStatus } from '$lib/types/taskflow';
	
	export let taskflow: Taskflow;
	
	// Track expanded state for nested taskflows
	let expandedTasksState = get(expandedTasks);
	
	expandedTasks.subscribe(value => {
		expandedTasksState = value;
	});
	
	function toggleTaskExpansion(taskId: string) {
		taskflowActions.toggleTaskExpansion(taskId);
	}
	
	function getStatusClass(status: TaskStatus): string {
		if (status === TaskStatus.SUCCESS) return 'bg-green-100 text-green-800';
		if (status === TaskStatus.RUNNING) return 'bg-yellow-100 text-yellow-800';
		if (status === TaskStatus.FAILED) return 'bg-red-100 text-red-800';
		if (status === TaskStatus.WAITING) return 'bg-gray-100 text-gray-600';
		return 'bg-gray-100 text-gray-800';
	}
	
	// Gather all tasks from all stages for flat display
	$: allTasks = taskflow.stages.flatMap(stage => 
		stage.tasks.map(task => ({
			...task, 
			stageName: stage.name,
			stageId: stage.id
		}))
	);
	
	// Function to check if a task has nested taskflow
	function hasNestedTaskflow(task: Task): boolean {
		return !!task.nestedTaskflowId;
	}
</script>
  
<div>
	<table class="min-w-full divide-y divide-gray-200">
		<thead class="bg-gray-50">
			<tr>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Name</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Type</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Stage</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Status</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Actions</th>
			</tr>
		</thead>
		<tbody class="bg-white divide-y divide-gray-200">
			{#each allTasks as task (task.id)}
				<!-- Regular task row -->
				<tr class={hasNestedTaskflow(task) ? "bg-blue-50 bg-opacity-30" : ""}>
					<td class="px-6 py-4 whitespace-nowrap text-sm text-gray-900">
						{#if hasNestedTaskflow(task)}
							<span class="flex items-center font-medium">
								<span class="mr-2 text-blue-600">↳</span>
								{task.name}
								<span class="ml-2 px-1.5 py-0.5 bg-blue-100 text-blue-800 text-xs rounded">Contains nested taskflow</span>
							</span>
						{:else}
							{task.name}
						{/if}
					</td>
					<td class="px-6 py-4 whitespace-nowrap text-sm text-gray-500">{task.type}</td>
					<td class="px-6 py-4 whitespace-nowrap text-sm text-gray-500">{task.stageName}</td>
					<td class="px-6 py-4 whitespace-nowrap">
						<span class="px-2 inline-flex text-xs leading-5 font-semibold rounded-full {getStatusClass(task.status as TaskStatus)}">
							{task.status}
						</span>
					</td>
					<td class="px-6 py-4 whitespace-nowrap text-sm">
						{#if hasNestedTaskflow(task)}
							<button 
								class="text-blue-600 hover:text-blue-800 font-medium"
								on:click={() => toggleTaskExpansion(task.id)}
							>
								{expandedTasksState.get(task.id) ? 'Collapse' : 'Expand'}
							</button>
						{:else}
							<button class="text-blue-600 hover:text-blue-800 font-medium">
								Details
							</button>
						{/if}
					</td>
				</tr>
				
				<!-- Nested taskflow rows (if expanded) -->
				{#if hasNestedTaskflow(task) && expandedTasksState.get(task.id)}
					<!-- Nested Taskflow Header -->
					<tr class="bg-blue-50 border-t border-blue-100">
						<td colspan="5" class="px-10 pt-2 pb-0">
							<div class="text-sm font-medium text-blue-800">Nested Taskflow: {task.nestedTaskflowId}</div>
						</td>
					</tr>
					<!-- This would display actual nested taskflow data if available -->
					<tr class="bg-blue-50 border-b border-blue-100">
						<td colspan="5" class="px-10 py-2">
							<div class="text-xs text-blue-600 font-medium">Nested taskflow details would be displayed here</div>
						</td>
					</tr>
					<!-- Placeholder for nested tasks -->
					<tr class="bg-blue-50 bg-opacity-50">
						<td class="px-12 py-3 whitespace-nowrap text-sm text-gray-900">
							<span class="ml-4">Nested Task</span>
						</td>
						<td class="px-6 py-3 whitespace-nowrap text-sm text-gray-500">ACTION</td>
						<td class="px-6 py-3 whitespace-nowrap text-sm text-gray-500">Nested Stage</td>
						<td class="px-6 py-3 whitespace-nowrap">
							<span class="px-2 inline-flex text-xs leading-5 font-semibold rounded-full bg-gray-100 text-gray-800">
								UNKNOWN
							</span>
						</td>
						<td class="px-6 py-3 whitespace-nowrap text-sm">
							<button class="text-blue-600 hover:text-blue-800 font-medium">
								Details
							</button>
						</td>
					</tr>
				{/if}
			{:else}
				<tr>
					<td colspan="5" class="px-6 py-4 text-center text-sm text-gray-500">
						No tasks found in this taskflow.
					</td>
				</tr>
			{/each}
		</tbody>
	</table>
</div>