<script lang="ts">
	import { onMount } from 'svelte';
	import { taskflows, taskflowActions } from '$lib/stores/taskflow';
	import StatusBadge from './StatusBadge.svelte';
	import LoadingSpinner from './LoadingSpinner.svelte';
	import ErrorMessage from './ErrorMessage.svelte';
    import type { Taskflow } from '$lib/types/taskflow';
    import { goto } from '$app/navigation';
	
	let isLoading = true;
	let error: Error | null = null;
	
	onMount(async () => {
	  try {
		isLoading = true;
		// await taskflowActions.fetchTaskflows();
		error = null;
	  } catch (e) {
		error = e instanceof Error ? e : new Error('Unknown error');
	  } finally {
		isLoading = false;
	  }
	});
	
	const handleTaskflowClick = async(taskflow: Taskflow) =>{
	  taskflowActions.setActiveTaskflow(taskflow);
	  await goto(`/taskflows/${taskflow.taskflowId}`);
	}
	
	async function handleRetry() {
	  try {
		isLoading = true;
		error = null;
		await taskflowActions.fetchTaskflows();
	  } catch (e) {
		error = e instanceof Error ? e : new Error('Unknown error');
	  } finally {
		isLoading = false;
	  }
	}
  </script>
  
  <div class="h-full">
	{#if isLoading}
	  <div class="h-full flex items-center justify-center">
		<LoadingSpinner />
	  </div>
	{:else if error}
	  <div class="h-full flex items-center justify-center">
		<div class="w-full max-w-2xl">
		  <ErrorMessage message={error.message} onRetry={handleRetry} />
		</div>
	  </div>
	{:else}
	  <div class="bg-white shadow-sm rounded-md overflow-hidden h-full">
		<div class="overflow-auto" style="max-height: calc(100vh - 190px);">
		  <table class="min-w-full divide-y divide-gray-200">
			<thead class="bg-gray-50 sticky top-0">
			  <tr>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Actions</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">ID</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Status</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Created At</th>
			  </tr>
			</thead>
			<tbody class="bg-white divide-y divide-gray-200">
			  {#each $taskflows as taskflow}
				<tr on:click={() => handleTaskflowClick(taskflow)} class="hover:bg-gray-50 cursor-pointer">
				  <td class="px-6 py-4 whitespace-nowrap text-sm font-medium">
					<button 
					  on:click={() => handleTaskflowClick(taskflow)}
					  class="text-blue-600 hover:text-blue-800 cursor-pointer"
					>
					  View
					</button>
				  </td>
				  <td class="px-6 py-4 whitespace-nowrap text-sm font-medium text-gray-900">{taskflow.taskflowId}</td>
				  <td class="px-6 py-4 whitespace-nowrap text-sm">
					<StatusBadge status={taskflow.status} />
				  </td>
				  <td class="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
					{new Date(Number(taskflow.createdAt)).toLocaleString()}
				  </td>
				</tr>
			  {:else}
				<tr>
				  <td colspan="5" class="px-6 py-4 text-center text-sm text-gray-500">
					No taskflows found. Add a new one or execute a template.
				  </td>
				</tr>
			  {/each}
			</tbody>
		  </table>
		</div>
	  </div>
	{/if}
  </div>