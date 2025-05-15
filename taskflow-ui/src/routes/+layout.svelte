<!-- <script lang="ts">

	import {onMount} from "svelte"
	import { startRealtimeEvents} from "$lib/taskflow-service"
	import {init} from "$lib"

	onMount( async()=>{
		await init()
		await startRealtimeEvents()
	})
</script> -->


<script lang="ts">
    import { get } from 'svelte/store';
	import '../app.css';
    import { taskflowActions, taskflows, taskflowsMap } from '$lib/stores/taskflow';
    import { onMount } from 'svelte';
    import { templateActions } from '$lib/stores/template';
    import { TaskflowApi } from '$lib/api/taskflow-api';
    import { init } from '$lib';
	import { browser } from '$app/environment';

	onMount(async()=>{
		// if(browser){
			// await init();	
		// 	await taskflowActions.fetchTaskflows();
		// 	await templateActions.fetchTemplates();
		// }
		// await startRealtimeEvents()
		// const temp = await TaskflowApi.GetAllTaskflows()
	})
  </script>
  
  <main>
	<slot />
  </main>