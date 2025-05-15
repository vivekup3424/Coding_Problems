<script lang="ts">
	import { createEventDispatcher, onMount } from 'svelte';
	import { templateActions } from '$lib/stores/template';
    import Button from './common/Button.svelte';
    import { TemplateApiCaller } from '$lib/api/template';
	import type { ITemplate, Template } from '$lib/types/template';
	import { Input, Textarea } from 'flowbite-svelte';
	
	export let show = false;
	export let mode: 'create' | 'update' = 'create';
	export let template: Template | null = null;
	
	const dispatch = createEventDispatcher();
	let loading = false;
	
	let configurationJson = '';
	let isSubmitting = false;
	let error: string | null = null;
    let parsedConfig: any = null;

	// We need to watch for changes to the 'show' and 'mode' props
	$: if (show) {
		resetForm();
	}
	
	$: if (mode === 'create' && show) {
		configurationJson = ""
	} else if (mode === 'update' && show && template) {
		configurationJson = JSON.stringify({
            name: template.name,
			options: template.options || {},
			context: template.context || {},
			stages: template.stages || []
		}, null, 2);
	}
    
    // Parse the configuration and extract the name when the JSON changes
    $: try {
        parsedConfig = JSON.parse(configurationJson);
    } catch (e) {
        parsedConfig = null;
    }
	
	function close() {
	  dispatch('close');
	  resetForm();
	}
	
	function resetForm() {
	  if (mode === 'create') {
		configurationJson = JSON.stringify({
            name: "New Template",
			options: {},
			context: {},
			stages: []
		}, null, 2);
	  } else if (mode === 'update' && template) {
		configurationJson = JSON.stringify({
            name: template.name,
			options: template.options || {},
			context: template.context || {},
			stages: template.stages || []
		}, null, 2);
	  }
	  error = null;
	}

	const handleCreateTemplate = async() => {
		try {
			loading = true;
			const parsedConfiguration = JSON.parse(configurationJson);
			
			if (mode === 'create') {
				await templateActions.createTemplate(parsedConfiguration);
				dispatch('createTemplate');
			} else if (mode === 'update' && template) {
				await templateActions.updateTemplate({
					templateId: template.templateId,
					...parsedConfiguration
				});
				dispatch('updateTemplate');
			}
			
			dispatch('close');
		} catch (err) {
			error = err instanceof Error ? err.message : 'An unknown error occurred';
		} finally {
			loading = false;
		}
	}
</script>
  
{#if show}
	<div class="fixed bg-white inset-0 bg-opacity-30 flex items-center justify-center z-50 h-full border-black">
	  <div class="bg-white rounded-lg shadow-xl w-full max-w-2xl mx-4">
		<div class="border-b border-gray-200 px-6 py-4 flex justify-between items-center">
		  <h3 class="text-lg font-medium text-gray-900">
			{mode === 'create' ? 'Create New Template' : 'Update Template'}
		  </h3>
		  <button 
			on:click={close} 
			class="text-gray-400 hover:text-gray-500"
		  >
			<svg class="h-6 w-6" fill="none" viewBox="0 0 24 24" stroke="currentColor">
			  <path stroke-linecap="round" stroke-linejoin="round" stroke-width={2} d="M6 18L18 6M6 6l12 12" />
			</svg>
		  </button>
		</div>
		
		<div class="px-6 py-4">
		  {#if error}
			<div class="mb-4 bg-red-50 text-red-700 p-3 rounded">
			  {error}
			</div>
		  {/if}
		  
		  <div class="mb-4">
            <div class="flex justify-between items-center">
              <!-- <span class="block text-sm font-medium text-gray-700">Template Configuration (JSON)</span> -->
              <!-- {#if parsedConfig?.name}
                <span class="text-sm text-blue-600">Name: {parsedConfig.name}</span>
              {/if} -->
            </div>
            <!-- <p class="text-xs text-gray-500 mb-2">Include template name, options, context, and stages in the JSON</p> -->
            <Textarea
              style="resize:none; font-family: monospace;"
              id="configuration"
              bind:value={configurationJson}
              rows={20}
              class="mt-1 block w-full font-mono text-sm"
            />
          </div>
		  
		  <div class="flex justify-end">
			<Button 
			  on:click={close}
			  class="mr-2 px-4 py-2 border border-gray-300 rounded-md shadow-sm text-sm font-medium text-gray-700 bg-white hover:bg-gray-50"
			>
			  Cancel
		  </Button>
			<Button bind:loading class="bg-blue-600 p-2" on:click={handleCreateTemplate}>
				{mode === 'create' ? 'Create Template' : 'Update Template'}
			</Button>
		  </div>
		</div>
	  </div>
	</div>
{/if}