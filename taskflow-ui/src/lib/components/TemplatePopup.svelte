<script lang="ts">
    import { goto } from '$app/navigation';
	import { selectedTemplate, showTemplatePopup, templateActions } from '$lib/stores/template';
    import Button from './common/Button.svelte';
	
	let isExecuting = false;
	let error: string | null = null;
	
	async function executeTemplate() {
	  if ($selectedTemplate) {
		try {
		  isExecuting = true;
		  error = null;
		  await templateActions.executeTemplate($selectedTemplate.id);
		  templateActions.closeTemplatePopup();
		  await goto("/")
		} catch (e) {
		  error = e instanceof Error ? e.message : 'Failed to execute template';
		} finally {
		  isExecuting = false;
		}
	  }
	}
  </script>
  
  {#if $showTemplatePopup && $selectedTemplate}
	<div class="fixed inset-0 bg-black bg-opacity-30 flex items-center justify-center z-50">
	  <div class="bg-white rounded-lg shadow-xl w-full max-w-2xl mx-4">
		<div class="border-b border-gray-200 px-6 py-4 flex justify-between items-center">
		  <h3 class="text-lg font-medium text-gray-900">Template Details</h3>
		  <button 
			on:click={templateActions.closeTemplatePopup} 
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
			<div class="text-sm font-medium text-gray-500">Template ID</div>
			<div class="mt-1 text-sm text-gray-900">{$selectedTemplate.id}</div>
		  </div>
		  
		  <div class="mb-4">
			<div class="text-sm font-medium text-gray-500">Name</div>
			<div class="mt-1 text-sm text-gray-900">{$selectedTemplate.name}</div>
		  </div>
		  
		  <div class="mb-4">
			<div class="text-sm font-medium text-gray-500">Category</div>
			<div class="mt-1 text-sm text-gray-900">{$selectedTemplate.category}</div>
		  </div>
		  
		  <div class="mb-4">
			<div class="text-sm font-medium text-gray-500">Created At</div>
			<div class="mt-1 text-sm text-gray-900">{$selectedTemplate.createdAt}</div>
		  </div>
		  
		  <div class="mb-4">
			<div class="text-sm font-medium text-gray-500">Template Configuration</div>
			<pre class="mt-1 bg-gray-50 p-2 rounded text-xs overflow-auto max-h-64">
  {JSON.stringify($selectedTemplate.configuration, null, 2)}
			</pre>
		  </div>
		</div>
		
		<div class="bg-gray-50 px-6 py-4 flex justify-end">
		  <Button 
			on:click={templateActions.closeTemplatePopup}
			class="mr-2 px-4 py-2 border border-gray-300 rounded-md shadow-sm text-sm font-medium text-gray-700 bg-white hover:bg-gray-50"
			disabled={isExecuting}
		  >
			Cancel
		</Button>
		  <button 
			on:click={executeTemplate}
			class="px-4 py-2 border border-transparent rounded-md shadow-sm text-sm font-medium text-white bg-blue-600 hover:bg-blue-700 disabled:opacity-50 disabled:cursor-not-allowed"
			disabled={isExecuting}
		  >
			{#if isExecuting}
			  <span class="flex items-center">
				<span class="mr-2 w-4 h-4 border-2 border-white border-t-transparent rounded-full animate-spin"></span>
				Executing...
			  </span>
			{:else}
			  Execute Template
			{/if}
		  </button>
		</div>
	  </div>
	</div>
  {/if}