<script lang="ts">
  import type { Stage, Task, Taskflow } from "$lib/types/taskflow";
  import StatusBadge from "$lib/components/StatusBadge.svelte";
  import { taskflowsMap } from "$lib/stores/taskflow";
  import { onMount, setContext } from "svelte";
  import NestedTaskflow from "../../NestedTaskflow.svelte";
  import { makeCopy } from "$lib/utils";
  import type { JSONCodec } from "@keus-automation/kiotp-realtime-js-web/nats-export";
  import { StageStatus, TaskStatus } from "$lib/types/taskflow";
  import TaskStatusBadge from "$lib/components/TaskStatusBadge.svelte";
  import Button from "$lib/components/common/Button.svelte";
  import TaskCard from "$lib/components/TaskCard.svelte";
  import Modal from "$lib/components/common/Modal.svelte";
  import { ChevronDown, ChevronRight } from "lucide-svelte";

  export let taskflow: Taskflow = {} as Taskflow;
  let stages: Stage[] = [];
  let debug = {
    hasData: false,
    stagesCount: 0,
    taskflow: null,
  };

  let expandedStages: Record<string, boolean> = {};
  let expandedNestedTaskflows: Record<string, boolean> = {};

  let showTaskDetailsModal = false;
  let selectedTask: Task | null = null;

  function handleOpenTaskDetails(task: Task) {
    selectedTask = task;
    showTaskDetailsModal = !showTaskDetailsModal;
  }

  setContext("expandedNestedTaskflows", expandedNestedTaskflows);

  function getStageBorderColor(status: StageStatus): string {
    if (status === StageStatus.COMPLETED) return "border-green-500";
    if (status === StageStatus.RUNNING) return "border-yellow-500";
    if (status === StageStatus.PARTIAL_COMPLETED) return "border-orange-500";
    if (status === StageStatus.FAILED) return "border-red-500";
    return "border-gray-300";
  }

  function getStageIndicatorColor(status: StageStatus): string {
    if (status === StageStatus.COMPLETED) return "bg-green-500";
    if (status === StageStatus.RUNNING) return "bg-yellow-500";
    if (status === StageStatus.PARTIAL_COMPLETED) return "bg-orange-500";
    if (status === StageStatus.FAILED) return "bg-red-500";
    return "bg-gray-300";
  }

  function getStageTextColor(status: StageStatus): string {
    if (status === StageStatus.COMPLETED) return "text-green-500";
    if (status === StageStatus.RUNNING) return "text-yellow-500";
    if (status === StageStatus.PARTIAL_COMPLETED) return "text-orange-500";
    if (status === StageStatus.FAILED) return "text-red-500";
    return "text-gray-300";
  }

  function getStageBorderColorForTasks(status: StageStatus): string {
    if (status === StageStatus.COMPLETED) return "border-green-300";
    if (status === StageStatus.RUNNING) return "border-yellow-300";
    if (status === StageStatus.PARTIAL_COMPLETED) return "border-orange-300";
    if (status === StageStatus.FAILED) return "border-red-300";
    return "border-gray-300";
  }

  function stageHasNestedTaskflows(stage: Stage): boolean {
    if (!stage.tasks) return false;

    const tasksArray: Task[] = Array.isArray(stage.tasks)
      ? stage.tasks
      : Object.values(stage.tasks as Record<string, Task>);

    return tasksArray.some(
      (task) =>
        task && (task.nestedTaskflowId || task?.nestedTaskflows?.length > 0),
    );
  }

  function getTasksFromStage(stage: Stage): Task[] {
    if (!stage.tasks) return [];

    return Array.isArray(stage.tasks)
      ? stage.tasks
      : Object.values(stage.tasks as Record<string, Task>);
  }

  function findNestedTaskflowTask(stage: Stage): Task | undefined {
    const tasks = getTasksFromStage(stage);
    return tasks.find(
      (t) => t && (t.nestedTaskflowId || t?.nestedTaskflows?.length > 0),
    );
  }

  function hasNestedTaskflows(task: Task): boolean {
    return (
      !!task.nestedTaskflowId ||
      (!!task.nestedTaskflows && task.nestedTaskflows.length > 0)
    );
  }

  function processTaskflow() {
    let currentTaskflow = $taskflowsMap.get(taskflow.taskflowId);

    if (currentTaskflow?.stages) {
      if (
        typeof currentTaskflow.stages === "object" &&
        !Array.isArray(currentTaskflow.stages)
      ) {
        stages = Object.values(currentTaskflow.stages as Record<string, Stage>);
      } else if (Array.isArray(currentTaskflow.stages)) {
        stages = [...currentTaskflow.stages];
      }

      debug.hasData = true;
      debug.stagesCount = stages.length;

      stages.forEach((stage) => {
        if (stage && stage.id && expandedStages[stage.id] === undefined) {
          expandedStages[stage.id] = true;
        }

        if (stage && stage.tasks) {
          const tasks = getTasksFromStage(stage);
          tasks.forEach((task) => {
            if (
              task &&
              task.id &&
              hasNestedTaskflows(task) &&
              expandedNestedTaskflows[task.id] === undefined
            ) {
              expandedNestedTaskflows[task.id] = true;
            }
          });
        }
      });
    } else {
      stages = [];
    }
  }

  function toggleStageExpand(stageId: string) {
    expandedStages[stageId] = !expandedStages[stageId];
    expandedStages = { ...expandedStages }; // Trigger reactivity
  }

  function toggleNestedTaskflow(taskId: string) {
    showTaskDetailsModal = false;
    expandedNestedTaskflows[taskId] = !expandedNestedTaskflows[taskId];
    expandedNestedTaskflows = { ...expandedNestedTaskflows }; // Trigger reactivity
  }

  function getTaskCount(stage: Stage): number {
    if (!stage || !stage.tasks) return 0;

    return Array.isArray(stage.tasks)
      ? stage.tasks.length
      : Object.keys(stage.tasks as Record<string, Task>).length;
  }

  function getTaskStatusClass(status: TaskStatus): string {
    if (status === TaskStatus.SUCCESS) return "border-green-200 bg-white";
    if (status === TaskStatus.RUNNING) return "border-yellow-200 bg-white";
    if (status === TaskStatus.FAILED) return "border-red-200 bg-white";
    return "border-gray-200 bg-white";
  }

  function formatStageStatus(status: StageStatus): string {
    if (status === StageStatus.COMPLETED) return "Completed";
    if (status === StageStatus.RUNNING) return "Running";
    if (status === StageStatus.PARTIAL_COMPLETED) return "Partial Completed";
    if (status === StageStatus.FAILED) return "Failed";
    return "Waiting";
  }

  let TASKFLOW: Taskflow = {} as Taskflow;

  onMount(async () => {
    TASKFLOW = await makeCopy(taskflow);
    processTaskflow();
  });

  // Update the stages when the store changes
  $: {
    $taskflowsMap;
    processTaskflow();
  }
</script>

<Modal
  bind:open={showTaskDetailsModal}
  title={selectedTask?.name || ""}
  class="modal-center-fix"
>
  {#if selectedTask}
    <div class="w-full p-6 space-y-4 text-gray-700">
      
      <!-- Task Type and Details -->
      <div class="text-sm font-medium text-gray-600">
        <span class="uppercase tracking-wide">Type: </span>
        <div class="font-mono">
            {#if selectedTask.taskDetails}
              {#if selectedTask.type === "ACTION" && selectedTask.taskDetails.serviceId && selectedTask.taskDetails.actionName}
                <span class="ml-2 text-gray-500">
                  {selectedTask.type} — {selectedTask.taskDetails.serviceId}.{selectedTask.taskDetails.actionName}
                </span>
              {:else if selectedTask.type === "CHANNEL" && selectedTask.taskDetails.channelName}
                <span class="ml-2 text-gray-500">
                {selectedTask.type} — {selectedTask.taskDetails.channelName}
                </span>
              {/if}
            {/if}
        </div>
      </div>

      <!-- Response Section -->
      <div class="text-sm">
        <div class="font-semibold text-gray-600">Response:</div>
        <div class="ml-2 text-gray-500">
          Success: <span class="font-mono">{selectedTask?.response?.success ? "true" : "false"}</span><br>
          Data: <span class="font-mono">
            {selectedTask?.response?.data ||
             selectedTask?.response?.response ||
             "null"}
          </span>
        </div>
      </div>

      <!-- Attempt and Status -->
      <div class="text-sm">
        <div class="font-semibold text-gray-600">Attempt: {selectedTask.attempt}</div>
        <!-- <div class="ml-2">{selectedTask.attempt}</div> -->
        <div class="mt-2">
          <TaskStatusBadge status={selectedTask.status} />
        </div>
      </div>

    </div>
  {/if}
</Modal>


<div class="p-4">
  {#if stages.length === 0}
    <div class="p-4 text-center text-gray-500 bg-gray-50 rounded">
      No stages found for this taskflow.
    </div>
  {:else}
    <div class="flex flex-col space-y-6">
      {#each stages as stage (stage.id)}
        <div
          class="{getStageBorderColor(
            stage.status,
          )} border-l-2 pl-6 pt-2 pb-6 relative"
        >
          <div
            class="absolute w-4 h-4 {getStageIndicatorColor(
              stage.status,
            )} rounded-full -left-2 top-2"
          ></div>
          <div>
            <div class="flex items-center">
              <h3 class="text-lg font-medium text-gray-900">{stage.name}</h3>
              {#if getTaskCount(stage) > 0}
                <Button
                  class="ml-2 text-blue-500 text-sm"
                  on:click={() => toggleStageExpand(stage.id)}
                >
                  {expandedStages[stage.id] ? "Collapse" : "Expand"}
                </Button>
              {/if}
            </div>
            <p class="text-sm text-gray-500 mt-1">
              {getTaskCount(stage)}
              {getTaskCount(stage) === 1 ? "Task" : "Tasks"}· 
              <span class="{getStageTextColor(stage.status)}">
                {formatStageStatus(stage.status,)}
              </span>
              
            </p>

            {#if stageHasNestedTaskflows(stage)}
              <div
                class="mt-2 bg-blue-50 p-2 rounded-md border border-blue-200 flex items-center"
              >
                <div class="w-3 h-3 bg-blue-500 rounded-full mr-2"></div>
                <span class="text-sm text-blue-700">
                  Contains nested taskflow in {findNestedTaskflowTask(stage)
                    ?.name || ""}
                </span>
              </div>
            {/if}

            {#if stage.tasks && expandedStages[stage.id]}
              <!-- <div
                class="mt-3 border-l {getStageBorderColorForTasks(
                  stage.status,
                )} pl-4"
              > -->
              {#each getTasksFromStage(stage) as task, i (task.id)}
                {#if hasNestedTaskflows(task)}
                  <!-- <div
                      class="{i < getTaskCount(stage) - 1
                        ? 'mb-2 '
                        : ''}bg-blue-50 p-2 rounded border border-blue-200 flex justify-between items-center"
                    >
                      <div>
                        <div
                          class="font-medium text-gray-700 flex items-center"
                        >
                          {task.name}
                          <span
                            class="ml-2 px-1.5 py-0.5 bg-blue-100 text-blue-800 text-xs rounded"
                          >
                            Contains nested taskflow
                          </span>
                        </div>
                        <div class="text-xs text-gray-500">
                          {task.type}
                          {task.taskDetails
                            ? task.type === "ACTION" &&
                              task.taskDetails.serviceId &&
                              task.taskDetails.actionName
                              ? `- ${task.taskDetails.serviceId}.${task.taskDetails.actionName}`
                              : task.type === "CHANNEL" &&
                                  task.taskDetails.channelId
                                ? `- ${task.taskDetails.channelId}`
                                : ""
                            : ""}
                        </div>
                      </div>
                      <div class="flex items-center justify-between">
                        <Button
                          class="ml-2 text-blue-600 hover:text-blue-800 text-xs"
                          on:click={() => toggleNestedTaskflow(task.id)}
                        >
                          {expandedNestedTaskflows[task.id]
                            ? "Hide Nested"
                            : "Show Nested"}
                        </Button>
                        <StatusBadge status={task.status} />
                      </div>
                    </div> -->
                    <TaskCard
                    hasNestedTaskflows={hasNestedTaskflows(task)}
                    expanded={expandedNestedTaskflows[task.id]}
                    {task}
                    countCondition={i < getTaskCount(stage) - 1}
                    onClick={handleOpenTaskDetails}
                    onToggleClick={() => toggleNestedTaskflow(task.id)}
                  />
                  
                  {#if expandedNestedTaskflows[task.id]}
                    {#if task.nestedTaskflows && task.nestedTaskflows.length > 0}
                      {#each task.nestedTaskflows as nestedTaskflowId}
                        {@const nestedTf = $taskflowsMap.get(nestedTaskflowId)}
                        {#if nestedTf}
                          <NestedTaskflow
                            onClick={handleOpenTaskDetails}
                            taskflow={nestedTf}
                            level={1}
                            status={nestedTf.status}
                          />
                        {/if}
                      {/each}
                    {:else if task.nestedTaskflowId}
                      {@const nestedTf = $taskflowsMap.get(
                        task.nestedTaskflowId,
                      )}
                      {#if nestedTf}
                        <NestedTaskflow
                          taskflow={nestedTf}
                          level={1}
                          name={task.name}
                          status={nestedTf.status}
                        />
                      {/if}
                    {/if}
                  {/if}
                {:else}
                  <TaskCard
                    {task}
                    countCondition={i < getTaskCount(stage) - 1}
                    onClick={handleOpenTaskDetails}
                  />
                {/if}
              {/each}
              <!-- </div> -->
            {/if}
          </div>
        </div>
      {/each}
    </div>
  {/if}
</div>

<style>
  .modal-center-fix .modal-container {
    top: 50% !important;
    left: 50% !important;
    transform: translate(-50%, -50%) !important;
  }
</style>
