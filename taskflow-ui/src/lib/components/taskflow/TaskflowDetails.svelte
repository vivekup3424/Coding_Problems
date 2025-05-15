<script lang="ts">
    import { page } from '$app/stores';
    import { onMount, onDestroy } from 'svelte';
    import TaskflowHeader from './TaskflowHeader.svelte';
    import OverviewCards from './OverviewCards.svelte';
    import TabsContainer from './TabsContainer.svelte';
    import TasksTab from './tabs/TasksTab.svelte';
    import VisualizationTab from './tabs/VisualizationTab.svelte';
    import NestingTab from './tabs/NestingTab.svelte';
    import LogsTab from './tabs/LogsTab.svelte';
    import StagesTab from './tabs/StagesTab.svelte';
    import { activeTaskflow, taskflowActions, taskflowsMap } from '$lib/stores/taskflow';
    import { alertStore } from '$lib/utils/alertStore';
    import Button from '../common/Button.svelte';
    // import { refreshEventSubscription } from '$lib/taskflow-service';
  
    export let data;
    
    // Set up reactive assignment of taskflow from data.taskflow 
    // or from the taskflowsMap store
    let taskflow = data.taskflow;
    let taskflowId = taskflow.taskflowId;
    let unsubscribe:any;
    
    let activeTab = 'stages';
    
    function handleBackToDashboard() {
      window.history.back();
    }
    
    function setActiveTab(tab:string) {
      activeTab = tab;
    }

    async function refreshTaskflow() {
      try {
        alertStore.show("Refreshing taskflow data...", "info");
        await taskflowActions.fetchTaskflows();
        alertStore.show("Taskflow data refreshed", "success");
      } catch (error) {
        console.error("Error refreshing taskflow:", error);
        alertStore.show("Error refreshing data", "error");
      }
    }

    onMount(async () => {
      console.log("TaskflowDetails component mounted for:", taskflowId);
      
      taskflowActions.setActiveTaskflow(taskflow);
      
      taskflowActions.initializeExpandedStates(taskflow);
      
      unsubscribe = taskflowsMap.subscribe($map => {
        const updatedTaskflow = $map.get(taskflowId);
        if (updatedTaskflow) {
          console.log("Updating taskflow from store:", updatedTaskflow);
          taskflow = updatedTaskflow;
        }
      });
      
    });

    onDestroy(() => {
      if (unsubscribe) unsubscribe();
      	taskflowActions.setActiveTaskflow(null);
    });

    $: stages = Object.values($taskflowsMap.get(taskflow.taskflowId)?.stages ?? {}) || [];
</script>
  
<div class="p-6">
    <div class="flex items-center justify-between mb-4">
        <div class="flex items-center text-sm text-gray-500">
            <Button 
                on:click={handleBackToDashboard}
                class="text-bule-500"
            >
                Dashboard
        </Button>
            <span class="mx-2">/</span>
            <span class="font-medium text-gray-800">{$taskflowsMap.get(taskflow.taskflowId)?.taskflowId}</span>
        </div>
        
        <Button 
            on:click={refreshTaskflow}
            class="px-3 py-1 border border-gray-300 rounded-md text-sm text-gray-600 hover:bg-gray-50"
        >
            Refresh
      </Button>
    </div>
    
    <TaskflowHeader {refreshTaskflow} {taskflow} />
    
    <OverviewCards {taskflow} />
    
    <TabsContainer {activeTab} {setActiveTab}>
        {#if activeTab === 'tasks'}
            <TasksTab {taskflow} />
        {:else if activeTab === 'visualization'}
            <VisualizationTab {taskflow} />
        {:else if activeTab === 'nesting'}
            <NestingTab {taskflow} />
        {:else if activeTab === 'logs'}
            <LogsTab {taskflow} />
        {:else if activeTab === 'stages'}
            <StagesTab {taskflow} />
        {/if}
    </TabsContainer>
</div>