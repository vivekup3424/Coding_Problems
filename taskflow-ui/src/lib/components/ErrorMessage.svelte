<script lang="ts">
	export let message: string;
	export let onRetry: (() => void) | null = null;
  </script>
  
  <div class="bg-red-50 border border-red-200 text-red-700 px-4 py-3 rounded relative" role="alert">
	<strong class="font-bold">Error:</strong>
	<span class="block sm:inline"> {message}</span>
	
	{#if onRetry}
	  <button 
		class="mt-2 px-3 py-1 bg-red-700 text-white text-sm font-medium rounded-md"
		on:click={onRetry}
	  >
		Retry
	  </button>
	{/if}
  </div>