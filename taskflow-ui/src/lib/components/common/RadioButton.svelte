<script lang="ts">
    import { createEventDispatcher } from 'svelte';

	export let className = '';
    type colorType =
        | "red"
        | "yellow"
        | "orange"
        | "green"
        | "purple"
        | "blue"
        | "light"
        | "dark"
        | "primary"
        | "none"
        | "alternative";
        
    export let color: colorType = "blue";
	export let activeClick = false;
	export { className as class };

	const dispatch = createEventDispatcher();

	const handleClick = () => {
		activeClick = !activeClick;
		dispatch('change');
		dispatch('click');
	};
</script>

<!-- svelte-ignore a11y-click-events-have-key-events -->
<!-- svelte-ignore a11y-no-static-element-interactions -->
<div
	class={`w-[18px] h-[18px] rounded-full flex justify-center items-center cursor-pointer my-auto ${className}`}
	on:click={handleClick}
>

	<div
		class="w-[10px] h-[10px] rounded-full"
        style="background-color: {activeClick ? color : 'transparent'}"
	></div>
</div>

