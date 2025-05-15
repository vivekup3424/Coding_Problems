<!-- src/lib/components/taskflow/TaskflowHierarchy.svelte -->
<script lang="ts">
	import { TaskflowStatus, type Taskflow } from "$lib/types/taskflow";
	import { taskflowsMap } from "$lib/stores/taskflow";
	import { TaskStatus } from '$lib/types/taskflow';
    import Button from "../common/Button.svelte";
    import { ChevronDown, ChevronRight } from "lucide-svelte";
    import TaskStatusBadge from "../TaskStatusBadge.svelte";
    import StageStatusBadge from "../StageStatusBadge.svelte";
  
	export let taskflow: Taskflow;
	export let level: number = 0;

	let expanded:Record<string,boolean> = {}
	
	// Get appropriate styling based on level
	const levelColors = [
	  'border-blue-500',    // Level 0 (initial call)
	  'border-purple-500',  // Level 1
	  'border-teal-500',    // Level 2
	  'border-pink-500',    // Level 3 
	  'border-indigo-500'   // Level 4+ 
	];
	
	const textColors = [
	  'text-blue-700',      // Level 0
	  'text-purple-700',    // Level 1 
	  'text-teal-700',      // Level 2
	  'text-pink-700',      // Level 3
	  'text-indigo-700'     // Level 4+
	];
	
	const bgColors = [
	  'bg-blue-50',     // Level 0
	  'bg-purple-50',   // Level 1
	  'bg-teal-50',     // Level 2
	  'bg-pink-50',     // Level 3
	  'bg-indigo-50'    // Level 4+
	];
	
	export let status: TaskflowStatus = TaskflowStatus.WAITING;
	
	function getBorderColor(status: TaskStatus): string {
		if (status === TaskStatus.SUCCESS) return 'border-green-500';
		if (status === TaskStatus.RUNNING) return 'border-yellow-500';
		if (status === TaskStatus.FAILED) return 'border-red-500';
		return 'border-gray-300';
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

	function getTextColor(status: TaskflowStatus): string {
	  if (status === TaskflowStatus.COMPLETED) return `text-green-600`;
	  if (status === TaskflowStatus.RUNNING) return `text-yellow-600`;
	  if (status === TaskflowStatus.PARTIAL_COMPLETED) return `text-red-600`;
    if (status === TaskflowStatus.WAITING) return `text-gray-600`;
	  return `text-gray-600`;
	}

	const handlerToggle = (e:Event,id:string) => {
		if(!(id in expanded)){
			expanded[id] = true
		}
		else{
			expanded[id] = !expanded[id]
		}
	}
	
	$: borderColor = levelColors[Math.min(level, levelColors.length - 1)];
	$: textColor = textColors[Math.min(level, textColors.length - 1)];
	$: bgColor = bgColors[Math.min(level, bgColors.length - 1)];
	
	$: stages = taskflow ? (Array.isArray(taskflow.stages) ? taskflow.stages : Object.values(taskflow.stages || {})) : [];
	$: name = taskflow?.name || (taskflow?.taskflowId ? taskflow.taskflowId.substring(0, 8) : "Unknown");
</script>
  
<div class="pl-5 border-l-2 {borderColor}">
	<div class="font-medium {textColor} mb-2">
	  {#if level === 0}
		{name} (Main)
	  {:else}
		{name}
	  {/if}
	  <span class="text-xs ml-2 px-2 py-0.5 rounded {bgColor} {getTextColor(status)}">
		{status}
	  </span>
	</div>
	
	{#each stages as stage}
	  <div class="pl-5 border-l-2 {getBorderColor(stage.status)} mb-2">
		<div class="font-medium {getTextColor(stage.status)}">
		 {stage.name} <StageStatusBadge status={stage.status} />
		</div>
		
		{#each Object.values(stage.tasks || {}) as task}
		  {#if hasNestedTaskflow(task)}
			<div class="pl-5 border-l-2 {levelColors[Math.min(level + 1, levelColors.length - 1)]} mb-2">
			  <div class="font-medium {textColors[Math.min(level + 1, textColors.length - 1)]}">
				<span class="{getTextColor(task.status)} cursor-pointer" on:click={(e)=>handlerToggle(e,task.id)}>
					{task.name}
				</span> <TaskStatusBadge status={task.status} /> → Nested Taskflow
				
			  </div>
			  {#if expanded[task.id]}
				
				{#each getNestedTaskflowIds(task) as nestedId}
					{@const nestedTaskflow = $taskflowsMap.get(nestedId)}
					{#if nestedTaskflow}
					<svelte:self taskflow={nestedTaskflow} level={level + 1} status={nestedTaskflow.status} />
					{:else}
					<div class="pl-5 text-gray-500 text-sm italic">
						Nested taskflow data not available
					</div>
					{/if}
				{/each}
			  {/if}
			</div>
		  {:else}
			<div class="pl-5 {getTextColor(task.status)} my-1">
			  {task.name}
			  <span class="text-xs ml-1 py-0.5 px-1.5 my-2 rounded {getTextColor(task.status)} bg-opacity-20">
				<TaskStatusBadge status={task.status} />
			  </span>
			</div>
		  {/if}
		{/each}
	  </div>
	{/each}
</div>