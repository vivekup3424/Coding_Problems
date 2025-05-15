<script lang="ts">
	import type { Taskflow } from "$lib/types/taskflow";
	import { taskflowsMap } from "$lib/stores/taskflow";
	import { alertStore } from "$lib/utils/alertStore";
	import { TaskflowApi } from "$lib/api/taskflow-api";
    import Button from "../common/Button.svelte";

	export let taskflow: Taskflow;
	export let refreshTaskflow:()=> void

	const handleCancelTaskflow = async ():void => {
		try {
			await TaskflowApi.cancelTaskflow(taskflow.taskflowId);
		} catch (error) {
			console.error("Failed to cancel taskflow:", error);
			alertStore.show("Failed to cancel taskflow", "error");
		}
	};

	const handleRetryTaskflow = async ():void => {
		try {
			await TaskflowApi.retryTaskflow(taskflow.taskflowId);
			await refreshTaskflow()
		} catch (error) {
			console.error("Failed to retry taskflow:", error);
			alertStore.show("Failed to retry taskflow", "error");
		}
	};

	// async function handleRetryTaskflow() {
	// 	try {
	// 		await TaskflowApi.retryTaskflow(taskflow.taskflowId);
	// 	} catch (error) {
			// console.error("Failed to retry taskflow:", error);
			// alertStore.show("Failed to retry taskflow", "error");
	// 	}
	// }

	$: currentTaskflow = $taskflowsMap.get(taskflow.taskflowId);
</script>

<!-- Taskflow header -->
<div class="bg-white shadow-sm rounded-md p-4 mb-6">
	<div class="flex justify-between">
		<div>
			<h1 class="text-xl font-bold text-gray-800">
				{currentTaskflow?.name ||
					`Taskflow ${taskflow.taskflowId.substring(0, 8)}`}
			</h1>
			<div class="text-sm text-gray-500 mt-1">
				ID: {taskflow.taskflowId}
				<span class="mx-2">•</span>
				Created: {new Date(Number(taskflow.createdAt)).toLocaleString()}
			</div>
		</div>
		<div class="flex space-x-2">
			<!-- {#if currentTaskflow?.status === 'WAITING'} -->
			<Button
				on:click={handleCancelTaskflow}
				class="px-3 py-1.5 border border-red-500 text-red-500 text-sm font-medium rounded-md hover:bg-red-50 transition-colors duration-200"
			>
				Cancel
			</Button>
			<!-- {/if} -->

			<!-- {#if currentTaskflow?.status === 'FAILED'} -->
			<Button
				on:click={handleRetryTaskflow}
				class="px-3 py-1.5 border border-blue-500 text-blue-500 text-sm font-medium rounded-md hover:bg-blue-50 transition-colors duration-200"
			>
				Retry
			</Button>
			<!-- {/if} -->
		</div>
	</div>
</div>
