<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import { taskflowActions } from '$lib/stores/taskflow';
	import Button from "$lib/components/common/Button.svelte"
    import { TaskflowApiCaller } from '$lib/api/taskflow';
    import { TaskflowApi } from '$lib/api/taskflow-api';
    import { goto } from '$app/navigation';
	export let show = false;
	
	const dispatch = createEventDispatcher();
	
	let configurationJson = '';
	let isSubmitting = false;
	let error: string | null = null;
	let loading = false;
	
	function close() {
	  dispatch('close');
	  resetForm();
	}
	
	function resetForm() {
	  configurationJson = '';
	  error = null;
	}
	
	async function handleSubmit() {
	  try {
		isSubmitting = true;
		error = null;
		
		let configuration;
		try {
		  configuration = JSON.parse(configurationJson);
		} catch (e) {
		  error = 'Invalid JSON format in configuration';
		  return;
		}
		
		// Submit the taskflow
		const result = await taskflowActions.executeTaskflow(configuration);
		
		if (result.success) {
		  close();
		  // Optionally navigate to the new taskflow details page
		  if (result.taskflow && result.taskflow._id) {
			await goto(`/taskflows/${result.taskflow.taskflowId}`)
		  } else {
			await goto('/')
		  }
		} else {
		  error = result.error instanceof Error ? result.error.message : 'Failed to create taskflow';
		}
	  } catch (e) {
		error = e instanceof Error ? e.message : 'An unknown error occurred';
	  } finally {
		isSubmitting = false;
	  }
	}

	const handleCreateTaskflow = async() => {
		loading = true
		const parsedConfiguration = JSON.parse(configurationJson);
		await TaskflowApi.executeTaskflow(parsedConfiguration)
		dispatch('close');
		dispatch("createTemplate")
		loading = false
	}
  </script>
  
  {#if show}
	<div class="fixed bg-white inset-0 bg-opacity-30 flex items-center justify-center z-50 border-black">
	  <div class="bg-white rounded-lg shadow-xl w-full max-w-2xl mx-4">
		<div class="border-b border-gray-200 px-6 py-4 flex justify-between items-center">
		  <h3 class="text-lg font-medium text-gray-900">Create New Taskflow</h3>
		  <button 
			on:click={close} 
			class="text-gray-400 hover:text-gray-500"
		  >
			<svg class="h-6 w-6" fill="none" viewBox="0 0 24 24" stroke="currentColor">
			  <path stroke-linecap="round" stroke-linejoin="round" stroke-width={2} d="M6 18L18 6M6 6l12 12" />
			</svg>
		  </button>
		</div>
		
		<form on:submit|preventDefault={handleSubmit} class="px-6 py-4">
		  {#if error}
			<div class="mb-4 bg-red-50 text-red-700 p-3 rounded">
			  {error}
			</div>
		  {/if}
		  
		  <div class="mb-4">
			<label for="configuration" class="block text-sm font-medium text-gray-700">Taskflow Configuration (JSON)</label>
			<p class="text-xs text-gray-500 mb-2">Define the stages and tasks for your new taskflow</p>
			<textarea
			  style="resize:none;"
			  id="configuration"
			  bind:value={configurationJson}
			  rows="20"
			  class="mt-1 block w-full px-3 py-2 border border-gray-300 rounded-md shadow-sm focus:outline-none focus:ring-blue-500 focus:border-blue-500 font-mono text-sm"
			></textarea>
		  </div>
		  
		  <div class="flex justify-end">
			<Button 
			  on:click={close}
			  class="mr-2 px-4 py-2 border border-gray-300 rounded-md shadow-sm text-sm font-medium text-gray-700 bg-white hover:bg-gray-50"
			  disabled={isSubmitting}
			>
			  Cancel
		  </Button>
			<Button bind:loading class="bg-blue-600 p-2" on:click={handleCreateTaskflow}>
				Create Taskflow
			</Button>
			<!-- <button 
			  type="submit"
			  class="px-4 py-2 border border-transparent rounded-md shadow-sm text-sm font-medium text-white bg-blue-600 hover:bg-blue-700 disabled:opacity-50 disabled:cursor-not-allowed"
			  disabled={isSubmitting}
			>
			  {#if isSubmitting}
				<span class="flex items-center">
				  <span class="mr-2 w-4 h-4 border-2 border-white border-t-transparent rounded-full animate-spin"></span>
				  Creating...
				</span>
			  {:else}
				Create Taskflow
			  {/if}
			</button> -->
		  </div>
		</form>
	  </div>
	</div>
  {/if}