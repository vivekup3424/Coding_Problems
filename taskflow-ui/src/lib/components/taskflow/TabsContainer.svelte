<script lang="ts">
	export let activeTab;
	export let setActiveTab;
	
	const tabs = [
	  { id: 'stages', label: 'Stages' },
	//   { id: 'tasks', label: 'Tasks' },
	//   { id: 'logs', label: 'Execution Log' },
	  { id: 'visualization', label: 'Visualization' },
	//   { id: 'nesting', label: 'Nesting Info' }
	];
  </script>
  
  <div class="bg-white shadow-sm rounded-md mb-6">
	<div class="border-b border-gray-200">
	  <nav class="flex -mb-px">
		{#each tabs as tab}
		  <button 
			on:click={() => setActiveTab(tab.id)}
			class="py-4 px-6 text-center border-b-2 font-medium text-sm {activeTab === tab.id ? 'border-blue-500 text-blue-600' : 'border-transparent text-gray-500'}"
		  >
			{tab.label}
		  </button>
		{/each}
	  </nav>
	</div>
	
	<!-- Tab content -->
	<div class="p-4">
	  <slot></slot>
	</div>
  </div>