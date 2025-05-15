<!-- src/lib/components/taskflow/tabs/VisualizationTab.svelte -->
<script lang="ts">
	import type { Taskflow } from "$lib/types/taskflow";
	import { taskflowsMap } from "$lib/stores/taskflow";
    import TaskflowHierarchy from "../TaskflowHierarchy.svelte";
	import { TaskStatus } from '$lib/types/taskflow';
	
	export let taskflow: Taskflow;
	export let status: TaskStatus = TaskStatus.WAITING;
	
	function getBorderColor(status: TaskStatus): string {
		if (status === TaskStatus.SUCCESS) return 'border-green-500';
		if (status === TaskStatus.RUNNING) return 'border-yellow-500';
		if (status === TaskStatus.FAILED) return 'border-red-500';
		return 'border-gray-300';
	}
	
	function getBgColor(status: TaskStatus): string {
		if (status === TaskStatus.SUCCESS) return 'bg-green-50';
		if (status === TaskStatus.RUNNING) return 'bg-yellow-50';
		if (status === TaskStatus.FAILED) return 'bg-red-50';
		return 'bg-gray-50';
	}
	
	function getTextColor(status: TaskStatus): string {
		if (status === TaskStatus.SUCCESS) return 'text-green-700';
		if (status === TaskStatus.RUNNING) return 'text-yellow-700';
		if (status === TaskStatus.FAILED) return 'text-red-700';
		return 'text-gray-700';
	}
	
	function hasNestedTaskflow(task: any): boolean {
	  return !!(task.nestedTaskflowId || (task.nestedTaskflows && task.nestedTaskflows.length > 0));
	}
	
	function getNestedTaskflowIds(task: any): string[] {
	  if (task.nestedTaskflowId) {
		return [task.nestedTaskflowId];
	  } else if (task.nestedTaskflows && task.nestedTaskflows.length > 0) {
		return task.nestedTaskflows;
	  }
	  return [];
	}
	
	$: currentTaskflow = $taskflowsMap.get(taskflow.taskflowId);
	$: stages = currentTaskflow ? (Array.isArray(currentTaskflow.stages) ? currentTaskflow.stages : Object.values(currentTaskflow.stages || {})) : [];
</script>
  
<div class="p-4 bg-white rounded-md">
	<div class="border-b border-gray-200 pb-4 mb-4">
	  <div class="font-medium text-gray-800 mb-4">Taskflow Hierarchy</div>
	  
	  <div class="text-sm">
		{#if currentTaskflow}
		  <TaskflowHierarchy taskflow={currentTaskflow} level={0} status={currentTaskflow.status} />
		{:else}
		  <div class="text-gray-500 italic">No taskflow data available</div>
		{/if}
	  </div>
	</div>
	
	<!-- Multi-level nesting diagram -->
	<div class="border border-gray-200 rounded-md p-4">
	  <div class="font-medium text-gray-800 mb-4">Nested Taskflow Diagram</div>
	  
	  <div class="flex flex-col items-center">
		<!-- Main taskflow -->
		<div class="border-2 border-blue-600 rounded-md p-2 mb-4 w-64 text-center bg-blue-50">
		  <div class="font-medium">{currentTaskflow?.name || `Taskflow ${taskflow.taskflowId.substring(0, 8)}`}</div>
		  <div class="text-sm text-gray-600">Main Taskflow</div>
		  <div class="text-xs mt-1 font-medium {getTextColor(currentTaskflow?.status || status)}">{currentTaskflow?.status}</div>
		</div>
		
		{#if stages.length > 0}
		  <div class="w-1 h-6 bg-gray-300"></div>
		  
		  <!-- First level of stages -->
		  <div class="grid grid-cols-3 gap-4 mb-6">
			{#each stages as stage}
			  <div class="border-2 {getBorderColor(stage.status)} {getBgColor(stage.status)} rounded-md p-2 text-center">
				<div class="font-medium">{stage.name}</div>
				<div class="text-xs {getTextColor(stage.status)}">{stage.status}</div>
				
				<!-- Show nested taskflow indicators if any -->
				{#each Object.values(stage.tasks || {}).filter(task => hasNestedTaskflow(task)) as task}
				  <div class="mt-1 text-xs text-blue-600 flex items-center justify-center">
					<span class="w-2 h-2 rounded-full bg-blue-500 mr-1"></span>
					<span>{task.name}</span>
				  </div>
				{/each}
			  </div>
			{/each}
		  </div>
		  
		  <!-- Check for nested taskflows and visualize them -->
		  {#each stages as stage}
			{#each Object.values(stage.tasks || {}).filter(task => hasNestedTaskflow(task)) as task}
			  {#each getNestedTaskflowIds(task) as nestedId, i}
				{@const nestedTaskflow = $taskflowsMap.get(nestedId)}
				{#if nestedTaskflow}
				  <div class="mt-2 flex flex-col items-center">
					<div class="border-l-2 border-dashed border-blue-500 h-6"></div>
					
					<div class="border-2 border-blue-500 rounded-md p-2 mb-4 w-64 text-center bg-blue-100">
					  <div class="font-medium">{nestedTaskflow.name || `Nested Taskflow`}</div>
					  <div class="text-sm text-blue-700">Level 1 Nested Taskflow</div>
					  <div class="text-xs text-blue-600">In task: {task.name}</div>
					  <div class="text-xs mt-1 font-medium {getTextColor(nestedTaskflow.status)}">{nestedTaskflow.status}</div>
					</div>
					
					<!-- Check for level 2 nested taskflows -->
					{#each Object.values(nestedTaskflow.stages || {}) as nestedStage}
					  {#each Object.values(nestedStage.tasks || {}).filter(t => hasNestedTaskflow(t)) as nestedTask}
						{#each getNestedTaskflowIds(nestedTask) as level2Id}
						  {@const level2Taskflow = $taskflowsMap.get(level2Id)}
						  {#if level2Taskflow}
							<div class="border-l-2 border-dashed border-purple-500 h-6"></div>
							
							<div class="border-2 border-purple-500 rounded-md p-2 mb-4 w-56 text-center bg-purple-50">
							  <div class="font-medium">{level2Taskflow.name || `L2 Nested Taskflow`}</div>
							  <div class="text-xs text-purple-700">Level 2 Nested Taskflow</div>
							  <div class="text-xs text-purple-600">In task: {nestedTask.name}</div>
							  <div class="text-xs mt-1 font-medium {getTextColor(level2Taskflow.status)}">{level2Taskflow.status}</div>
							</div>
						  {/if}
						{/each}
					  {/each}
					{/each}
				  </div>
				{/if}
			  {/each}
			{/each}
		  {/each}
		{:else}
		  <div class="text-gray-500 italic mt-4">No stages found in this taskflow</div>
		{/if}
	  </div>
	</div>
</div>