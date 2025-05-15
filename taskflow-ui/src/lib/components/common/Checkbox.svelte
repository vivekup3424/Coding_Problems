<script lang="ts">
	import { createEventDispatcher } from 'svelte';

	export let label = '';
	export let id: string = '';
	export let checked = false;
	export let group: any[] = [];
	export let value = '';
	export let style = '';
	let className = "";
	export {className as class}
    
	const dispatch = createEventDispatcher();

	const handleOnChange = (e: Event) => {
		if (checked && !group.includes(value)) {
			group = [...group, value];
		} else if (!checked) {
			group = group.filter((x) => x != value);
		}
		dispatch('change', e);
	};

	const handleGroupChange = () => {
		if (group.includes(value)) {
			checked = true;
		}
	};

	$: {
		if (group) {
			handleGroupChange();
		}
	}
</script>

<div class="flex items-center {className}">
	<input
		type="checkbox"
		id={id}
		class="form-checkbox text-blue-600 h-4 w-4 rounded border-gray-300 focus:ring-blue-500 cursor-pointer"
		bind:checked
		on:change={handleOnChange}
		{value}
	/>
	{#if label}
		<label class="ml-2 text-gray-700" for={id}>{label}</label>
	{/if}
</div>

<style lang="scss">
	input {
		&:checked {
			background-color: #185eaf; 
		}
		&:focus {
			box-shadow: none;
		}
	}
</style>
