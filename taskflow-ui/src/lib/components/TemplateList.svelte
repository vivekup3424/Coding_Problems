<script lang="ts">
	import { onMount } from 'svelte';
	import { templates, templateActions } from '$lib/stores/template';
	import LoadingSpinner from './LoadingSpinner.svelte';
	import ErrorMessage from './ErrorMessage.svelte';
    import Loader from './common/Loader.svelte';
    import Button from './common/Button.svelte';
    import { alertStore } from '$lib/utils/alertStore';
    import { createEventDispatcher } from 'svelte';
	
	let isLoading = true;
	let error: Error | null = null;
	let executionLoading = false;
	let deleteLoading: Record<string, boolean> = {};
	
	const dispatch = createEventDispatcher();
	
	onMount(async () => {
	  try {
		isLoading = true;
		// await templateActions.fetchTemplates();
		error = null;
	  } catch (e) {
		error = e instanceof Error ? e : new Error('Unknown error');
	  } finally {
		isLoading = false;
	  }
	});
	
	function handleTemplateClick(template:any) {
	//   templateActions.showTemplateDetails(template);
	}
	
	const handleExecuteTemplate = async(templateId:string, event:any) => {
		executionLoading = true;
	 	event.stopPropagation();
		await templateActions.executeTemplate(templateId);
		executionLoading = false;
	}
	
	const handleUpdateTemplate = (template:any, event:any) => {
		event.stopPropagation();
		dispatch('updateTemplate', template);
	}
	
	const handleDeleteTemplate = async(templateId:string, event:any) => {
		event.stopPropagation();
		deleteLoading[templateId] = true;
		
		try {
			await templateActions.deleteTemplate(templateId);
			alertStore.show('Template deleted successfully', 'success');
			await templateActions.fetchTemplates();
		} catch (error) {
			console.error('Failed to delete template:', error);
			alertStore.show('Failed to delete template', 'error');
		} finally {
			deleteLoading[templateId] = false;
		}
	}
	
	async function handleRetry() {
	  try {
		isLoading = true;
		error = null;
		await templateActions.fetchTemplates();
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
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">ID</th>
				<th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Name</th>
				<!-- <th scope="col" class="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Created At</th> -->
				<th scope="col" class="px-6 py-3 text-right text-xs font-medium text-gray-500 uppercase tracking-wider">Actions</th>
			  </tr>
			</thead>
			<tbody class="bg-white divide-y divide-gray-200">
			  {#each $templates as template (template.templateId)}
				<tr 
				  class="hover:bg-gray-50 cursor-pointer"
				  on:click={() => handleTemplateClick(template)}
				>
				  <td class="px-6 py-4 whitespace-nowrap text-sm font-medium text-gray-900">{template.templateId}</td>
				  <td class="px-6 py-4 whitespace-nowrap text-sm text-gray-900">{template.name}</td>
				  <!-- <td class="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
					{new Date(Number(template.createdAt)).toLocaleString()}
				  </td> -->
				  <td class="px-6 py-4 whitespace-nowrap text-right text-sm font-medium">
					<div class="flex justify-end space-x-2">
						<Button 
							class="bg-blue-600 text-white px-3 py-1.5"
							on:click={(e) => handleUpdateTemplate(template, e)}
						>
							Update
						</Button>
						
						<Button
							bind:loading={deleteLoading[template.templateId]}
							class="bg-red-600 text-white px-3 py-1.5"
							on:click={(e) => handleDeleteTemplate(template.templateId, e)}
						>
							Delete
						</Button>
						
						<Loader bind:loading={executionLoading}>
							<button 
							  on:click={(e) => handleExecuteTemplate(template.templateId, e)}
							  class="text-white bg-green-600 hover:bg-green-700 px-3 py-1.5 rounded-md"
							>
							  Execute
							</button>
						</Loader>
					</div>
				  </td>
				</tr>
			  {:else}
				<tr>
				  <td colspan="5" class="px-6 py-4 text-center text-sm text-gray-500">
					No templates found. Add a new template to get started.
				  </td>
				</tr>
			  {/each}
			</tbody>
		  </table>
		</div>
	  </div>
	{/if}
</div>