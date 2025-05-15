import { writable, derived, get } from 'svelte/store';
import type { Stage, Task, Taskflow, TaskStatus } from '$lib/types/taskflow';
import { TaskflowApiCaller } from '$lib/api/taskflow';
import { alertStore } from '$lib/utils/alertStore';
import type { TaskflowApiRequest } from '$lib/api/interfaces';
import { TaskflowApi } from '$lib/api/taskflow-api';

export const taskflowsMap = writable<Map<string, Taskflow>>(new Map());

export const taskflows = derived(taskflowsMap, $map => Array.from($map.values()));

export const activeTaskflow = writable<Taskflow | null>(null);
export const activeTaskflowTab = writable<string>('stages');

export const expandedTasks = writable<Map<string, boolean>>(new Map());
export const expandedStages = writable<Map<string, boolean>>(new Map());

export const taskflowActions = {
  async fetchTaskflows() {
    try {
      const data = await TaskflowApi.GetAllTaskflows();

      const newMap = new Map<string, Taskflow>();
      data.forEach(taskflow => {
        newMap.set(taskflow.taskflowId, taskflow);
      });
      taskflowsMap.set(newMap);
      return { success: true };
    } catch (error) {
      console.error('Failed to fetch taskflows:', error);
      return { success: false, error };
    }
  },

  async executeTaskflow(taskflow: TaskflowApiRequest.ExecuteTaskflow) {
    try {
      const newTaskflow = await TaskflowApi.executeTaskflow(taskflow);

      taskflowsMap.update(map => {
        const newMap = new Map(map);
        newMap.set(newTaskflow._id, newTaskflow);
        return newMap;
      });

      return { success: true, taskflow: newTaskflow };
    } catch (error) {
      console.error('Failed to execute taskflow:', error);
      return { success: false, error };
    }
  },

  // New method to handle complete taskflow updates


  updateTaskflowStatus(id: string, status: string) {
    taskflowsMap.update(map => {
      const newMap = new Map(map);
      const taskflow = newMap.get(id);

      if (taskflow) {
        newMap.set(id, { ...taskflow, status });
      }

      return newMap;
    });
  },

  initializeExpandedStates(taskflow: Taskflow) {
    expandedStages.update(map => {
      const newMap = new Map(map);
      taskflow.stages.forEach(stage => {
        if (!newMap.has(stage.id)) {
          newMap.set(stage.id, true);
        }
      });
      return newMap;
    });

    expandedTasks.update(map => {
      const newMap = new Map(map);
      taskflow.stages.forEach(stage => {
        stage.tasks.forEach(task => {
          if (task.nestedTaskflowId && !newMap.has(task.id)) {
            newMap.set(task.id, true);
          }
        });
      });
      return newMap;
    });
  },

  toggleTaskExpansion(taskId: string) {
    expandedTasks.update(map => {
      const newMap = new Map(map);
      newMap.set(taskId, !newMap.get(taskId));
      return newMap;
    });
  },

  toggleStageExpansion(stageId: string) {
    expandedStages.update(map => {
      const newMap = new Map(map);
      newMap.set(stageId, !newMap.get(stageId));
      return newMap;
    });
  },

  setActiveTaskflow(taskflow: Taskflow) {
    activeTaskflow.set(taskflow);
  },

  setActiveTaskflowTab(tab: string) {
    activeTaskflowTab.set(tab);
  },

  addTaskflow(taskflow: Taskflow) {
    taskflowsMap.update(map => {
      const newMap = new Map(map);
      newMap.set(taskflow.taskflowId, taskflow);
      return newMap;
    });
  },

  updateTaskflow(taskflow: Taskflow) {
    taskflowsMap.update(map => {
      const newMap = new Map(map);
      newMap.set(taskflow.taskflowId, taskflow);
      return newMap;
    });
  },

  updateStage(taskflow: Taskflow, stageId: string, status: string) {
    // console.log("taskflow---",taskflow)
    // activeTaskflow.set(taskflow)
    // console.log("taskflowsMap---", get(taskflowsMap))
    taskflowsMap.update(map => {
      const newMap = new Map(map);
      const existingTaskflow = newMap.get(taskflow.taskflowId);

      if (existingTaskflow) {
        const stageArray: Stage[] = Array.isArray(existingTaskflow.stages)
          ? existingTaskflow.stages
          : Object.values(existingTaskflow.stages);

        const updatedStages = stageArray.map(stage => {
          if (stage.id === stageId) {
            return {
              ...stage,
              status
            };
          }
          return stage;
        });

        newMap.set(taskflow.taskflowId, {
          ...existingTaskflow,
          stages: updatedStages
        });
      }

      return newMap;
    });
  },
  updateTask(taskflow: Taskflow, taskId: string, status: TaskStatus) {
    // console.log("taskflow.createdAt---",taskflow.createdAt)
    // activeTaskflow.set(taskflow)
    taskflowsMap.update(map => {
      const newMap = new Map(map);
      const existingTaskflow = newMap.get(taskflow.taskflowId);

      if (existingTaskflow) {
        const stageArray: Stage[] = Array.isArray(existingTaskflow.stages)
          ? existingTaskflow.stages
          : Object.values(existingTaskflow.stages);

        const updatedStages = stageArray.map(stage => {
          const taskArray: Task[] = Array.isArray(stage.tasks)
          ? stage.tasks
          : Object.values(stage.tasks);
          const updatedTasks = taskArray.map(task => {
            if (task.id === taskId) {
              return {
                ...task,
                status
              };
            }
            return task;
          });

          return {
            ...stage,
            tasks: updatedTasks
          };
        });

        newMap.set(taskflow.taskflowId, {
          ...existingTaskflow,
          stages: updatedStages
        });
      }

      return newMap;
    });
  }
};