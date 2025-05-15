<script>
    import Loader from '$lib/components/common/Loader.svelte';
    import TaskflowDetails from '$lib/components/taskflow/TaskflowDetails.svelte';
    import RealtimeConnector from '$lib/realtime-connector';

	
	export let data;
	let loading = true;

	$:{
		if(data?.taskflow){
			loading = false;
		}
	}

	// $: console.log("RealtimeConnector.isConnected---",RealtimeConnector.isConnected,data)

  </script>
  
  {#if data.error}
	<div class="p-6 text-red-500">
	  Error: {data.error.message}
	</div>
  {:else if !data.taskflow}
	<div class="p-6">Loading taskflow details...</div>
  {:else}
  <Loader class="h-screen flex items-center justify-center" bind:loading>
	  <TaskflowDetails {data} />
  </Loader>
  {/if}