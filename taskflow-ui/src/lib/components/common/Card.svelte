<script lang="ts">
	import { Card } from 'flowbite-svelte';
	export let noShadow = false;
	export let style = '';
	export let className = '';
	export { className as class };
	$: classes =
		`${!noShadow ? 'shadow-lightNormal dark:shadow-darkNormal' : ''} p-2 w-fit dark:text-white ${className}`.trim();
</script>

<Card class="card-main {classes}" {style} padding="none" on:click>
		<slot />
</Card>
