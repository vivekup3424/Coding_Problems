<script lang="ts">
	import { onMount } from 'svelte';

	type State = 'danger' | 'ok';

	export let placeholder = '';
	export let value = '';
	export let state: State = 'ok';
	export let error = '';
	export let focus = false;
	let className = '';
	let inputField: HTMLInputElement;
	export { className as class };

	onMount(() => {
		if (focus) {
			inputField.focus();
		}
	});
</script>

<div class="inline-block mb-3 w-full">
	<input
		maxlength="30"
		bind:this={inputField}
		class={`shadow-normal text-sm ${className} ${state === 'danger' ? 'border-red-500' : 'border-gray-400'} outline-none rounded-lg w-full p-3`}
		{placeholder}
		bind:value
		on:change
		on:focus
		on:focusout
		on:input
		on:blur
	/>
	{#if state === 'danger' && error}
		<p class="text-red-500 text-xs mt-1">{error}</p>
	{/if}
</div>
