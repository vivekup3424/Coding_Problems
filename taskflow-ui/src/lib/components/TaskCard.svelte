<script lang="ts">
	import type { Task } from "$lib/types/taskflow";
	import { ChevronDown, ChevronRight } from "lucide-svelte";
	import Button from "./common/Button.svelte";
	import TaskStatusBadge from "./TaskStatusBadge.svelte";

	export let task: Task = {} as Task;
	export let countCondition = false;
	export let hasNestedTaskflows = false;
	export let expanded = false;
	export let onClick: (task: Task) => void;
	export let onToggleClick: (id: string) => void = () => {};


	const handlerToggle = (e:Event,id:string) => {
		e.stopPropagation()
		onToggleClick(task.id)
	}
</script>

<div
	on:click={() => onClick(task)}
	class="w-full border p-3 rounded-2xl flex justify-between items-center cursor-pointer mb-2"
>
	<div class="flex items-center space-x-3">

		<div class="text-gray-700 flex items-center gap-x-3">
			<div class="text-lg font-semibold cursor-pointer" on:click={(e)=>handlerToggle(e,task.id)}>{task.name}</div>
			{#if hasNestedTaskflows}
				<div class="text-xs text-blue-500">Contains nested taskflow</div>
			{/if}
		</div>
	</div>

	<div class="flex flex-col items-end text-sm text-gray-600">
		<div>Attempt: {task.attempt}</div>
		<TaskStatusBadge status={task.status} />
	</div>
</div>
