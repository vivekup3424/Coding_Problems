<script lang="ts">
	import { templateActions } from "$lib/stores/template";
	import type { Template } from "$lib/types/template";
	import Button from "./common/Button.svelte";

	export let template: Template;
	export let onClick: (template: Template) => void;
	export let onExecute: (template: Template, event: Event) => void;
	let executionLoading = false;

	const handleTemplateExecute = async (templateId: string) => {
		executionLoading = true
		await templateActions.executeTemplate(templateId);
		executionLoading = false
	};
</script>


	<div class="w-full flex p-3 gap-x-3 items-center justify-between cursor-pointer"
	on:click={() => onClick(template)} >
		<span class="text-sm font-medium w-1/4 text-center">{template.templateId}</span>
		<span class="text-sm w-1/5 text-center">{template.name}</span>
		<!-- <span class="text-sm w-1/5">{template.category}</span> -->
		<span class="text-sm w-1/5 text-center">
			{new Date(Number(template.createdAt)).toLocaleString()}
		</span>
		<span class="text-center w-1/5">
			<Button bind:loading={executionLoading} class="bg-blue-600 text-white px-4 py-1.5" on:click={() => handleTemplateExecute(template.templateId)}>
				Execute
			</Button>
		</span>
	</div>

