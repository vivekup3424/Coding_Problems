<script lang="ts">
	import { StageStatus, type Stage, type Task, type Taskflow } from "$lib/types/taskflow";
	import { TaskStatus, TaskflowStatus } from '$lib/types/taskflow';
	import StatusBadge from "$lib/components/StatusBadge.svelte";
	import TaskStatusBadge from "$lib/components/TaskStatusBadge.svelte";
	import { taskflowsMap } from "$lib/stores/taskflow";
	import { getContext } from 'svelte';
    import TaskCard from "./TaskCard.svelte";
	
	export let taskflow: Taskflow;
	export let name: string = "Nested Taskflow";
	export let level: number = 0; 
	export let status: TaskflowStatus = TaskflowStatus.WAITING;
  export let onClick: (task: Task) => void;
	
	let expandedNestedTaskflows = getContext<Record<string, boolean>>('expandedNestedTaskflows');
	
	const levelColors = [
	  'blue',    
	  'purple',  
	  'teal',   
	  'pink',  
	  'indigo' 
	];
	
	function getColor(level: number): string {
	  return levelColors[Math.min(level, levelColors.length - 1)];
	}
	
	function getBorderColor(level: number): string {
	  return `border-${getColor(level)}-300`;
	}
	
	function getTextColor(status: TaskflowStatus): string {
	  if (status === TaskflowStatus.COMPLETED) return `text-green-600`;
	  if (status === TaskflowStatus.RUNNING) return `text-yellow-600`;
	  if (status === TaskflowStatus.PARTIAL_COMPLETED) return `text-red-600`;
    if (status === TaskflowStatus.WAITING) return `text-gray-600`;
	  return `text-gray-600`;
	}
	
	// function getStageStatusColor(status: StageStatus): string {
	//   if (status === TaskStatus.SUCCESS) return `text-green-600`;
	//   if (status === TaskStatus.RUNNING) return `text-yellow-600`;
	//   if (status === TaskStatus.FAILED) return `text-red-600`;
	//   return `text-gray-600`;
	// }

  function getStageTextColor(status: StageStatus): string {
	  switch (status) {
		case StageStatus.COMPLETED: return 'text-green-800';
		case StageStatus.RUNNING: return 'text-yellow-800';
		case StageStatus.FAILED: return 'text-red-800';
		case StageStatus.WAITING: return 'text-gray-800';
		case StageStatus.PARTIAL_COMPLETED: return "text-orange-800"
		default: return 'text-gray-700';
	  }
	}
	
	function getTaskStatusClass(status: TaskStatus): string {
	  if (status === TaskStatus.SUCCESS) return "border-green-200 bg-white";
	  if (status === TaskStatus.RUNNING) return "border-yellow-200 bg-white";
	  if (status === TaskStatus.FAILED) return "border-red-200 bg-white";
	  return "border-gray-200 bg-white";
	}
	
	function formatStageStatus(status: StageStatus): StageStatus {
	  if (status === StageStatus.COMPLETED) return StageStatus.COMPLETED;
	  if (status === StageStatus.RUNNING) return StageStatus.RUNNING;
	  if (status === StageStatus.WAITING) return StageStatus.WAITING;
    if (status === StageStatus.PARTIAL_COMPLETED) return StageStatus.PARTIAL_COMPLETED;
    return StageStatus.WAITING
	}
	
	function getTasksFromStage(stage: Stage): Task[] {
	  if (!stage.tasks) return [];
	  return Array.isArray(stage.tasks) 
		? stage.tasks 
		: Object.values(stage.tasks as Record<string, Task>);
	}
	
	function hasNestedTaskflows(task: Task): boolean {
	  return !!task.nestedTaskflowId || (!!task.nestedTaskflows && task.nestedTaskflows.length > 0);
	}
	
	function toggleNestedTaskflow(taskId: string) {
	  expandedNestedTaskflows[taskId] = !expandedNestedTaskflows[taskId];
	}
	
	$: stages = taskflow?.stages ? 
	  (Array.isArray(taskflow.stages) ? taskflow.stages : Object.values(taskflow.stages as Record<string, Stage>)) 
	  : [];
	
	$: taskflowName = name || taskflow?.name || "Nested Taskflow";
</script>

<div class="mt-1 ml-4 {getBorderColor(level)} border-l-2 pl-4 py-2">
  <div class="text-sm font-medium {getTextColor(level)} mb-2">
    <!-- {#if level > 0}Level {level}: {/if}  -->
    <!-- <span class="text-sm font-medium {getTextColor(taskflow.status)}">
      <span class="text-xs font-medium"> 
        {taskflow.status}
      </span>
    </span>  -->
  </div>

  {#if stages.length > 0}
    {#each stages as stage (stage.id)}
      <div class="mb-2">
        <div class="text-xs {getColor(level)} font-medium mb-1">
         {stage.name} · 
          <span class="{getStageTextColor(stage.status)}">{formatStageStatus(stage.status)}</span>
        </div>
        <div class="pl-3 border-l {getBorderColor(level)} border-opacity-50">
          {#each getTasksFromStage(stage) as task, i (task.id)}
            {#if hasNestedTaskflows(task)}
              <div class="{i < getTasksFromStage(stage).length - 1 ? 'mb-1 ' : ''}bg-{getColor(level)}-50 p-1.5 rounded border border-{getColor(level)}-200 flex justify-between items-center">
                <div class="flex items-center">
                   <button 
                    class="mr-1 text-{getColor(level+1)}-600 hover:text-{getColor(level+1)}-800 text-xs text-blue-600 cursor-pointer"
                    on:click={() => toggleNestedTaskflow(task.id)}
                   >
                     {expandedNestedTaskflows[task.id] ? 'Hide' : 'Show'}
                   </button>
                  <div class="text-xs text-gray-700 flex items-center">
                    {task.name}
                    <!-- <span class="ml-1 px-1 py-px bg-{getColor(level+1)}-100 text-{getColor(level+1)}-800 text-xs rounded">
                      L{level + 1} nested
                    </span> -->
                  </div>
                </div>
                <div class="flex flex-col text-sm">

                  <span class=" text-gray-600">Attempt: {task.attempt}</span>
                  <!-- <span class="ml-2">{task.attempt}</span> -->
                  <TaskStatusBadge status={task.status} />
                </div>
              </div>
               {#if expandedNestedTaskflows[task.id]}
                 {#if task.nestedTaskflows && task.nestedTaskflows.length > 0}
                   {#each task.nestedTaskflows as nestedTaskflowId}
                     {@const nestedTf = $taskflowsMap.get(nestedTaskflowId)}
                     {#if nestedTf}
                        <!-- Recursive Call -->
                        <svelte:self 
                          taskflow={nestedTf} 
                          level={level + 1}
                          name={nestedTf.name}
                        />
                     {/if}
                   {/each}
                 {:else if task.nestedTaskflowId}
                   {@const nestedTf = $taskflowsMap.get(task.nestedTaskflowId)}
                   {#if nestedTf}
                      <!-- Recursive Call -->
                      <svelte:self 
                        taskflow={nestedTf} 
                        level={level + 1}
                        name={nestedTf.name}
                      />
                   {/if}
                 {/if}
               {/if}
            {:else}
              <!-- <div class="{i < getTasksFromStage(stage).length - 1 ? 'mb-0.5 ' : ''}{getTaskStatusClass(task.status)} p-1 rounded border flex flex-col">
                <div class="flex justify-between">

                  <div class="text-xs text-gray-700">{task.name}</div>
                  
                  <TaskStatusBadge status={task.status} />
                </div>
                <div>
                    <div class="text-xs text-gray-500">
                      {task.type} {task.taskDetails ? 
                        task.type === 'ACTION' && task.taskDetails.serviceId && task.taskDetails.actionName ? 
                          `- ${task.taskDetails.serviceId}.${task.taskDetails.actionName}` : 
                        task.type === 'CHANNEL' && task.taskDetails.channelId ? 
                          `- ${task.taskDetails.channelId}` : 
                        '' : ''}
                    </div>
                    <div class="text-xs text-gray-500">
                      Response: {
                        `[Success: ${task?.response?.success},Data: ${task?.response?.data}]`
                      }
                    </div>
                </div>
              </div> -->
              <TaskCard {onClick} {task} countCondition={i < getTasksFromStage(stage).length - 1} />
            {/if}
          {/each}
        </div>
      </div>
    {/each}
  {:else}
     <p class="text-xs text-gray-500 italic">No stages in this nested taskflow.</p>
  {/if}
</div>

<!-- <div class="border-2 {getBorderColor(level)} p-4 rounded-lg"> -->
	<!-- <span class="text-sm font-medium {getTextColor(status)}">
    <span class="text-xs font-medium"> 
      {status}
    </span>
  </span>  -->
<!-- </div> -->