<script lang="ts">
	import { Button, Badge } from 'flowbite-svelte';
	import Loader from './Loader.svelte';
	type colorType =
		| 'red'
		| 'yellow'
		| 'green'
		| 'purple'
		| 'blue'
		| 'light'
		| 'dark'
		| 'primary'
		| 'none'
		| 'alternative';

	type badgeColorType =
		| 'dark'
		| 'red'
		| 'yellow'
		| 'green'
		| 'indigo'
		| 'purple'
		| 'pink'
		| 'blue'
		| 'primary'
		| 'none';

	type sizeType = 'sm' | 'lg' | 'md' | 'xl' | 'xs';

	export let color: colorType = 'blue';
	let className: string = '';
	export { className as class };
	export let outlined = false;
	export let size: sizeType = 'md';
	export let circle = false;
	export let badge = false;
	export let badgeTxt = '';
	export let badgeColor: badgeColorType = 'blue';
	export let loading = false;
	export let disabled = false;
	export let style = '';
	export let pill = false;
	export let noShadow = false;
</script>

<Button
	{disabled}
	{style}
	{size}
	outline={outlined}
	{color}
	{pill}
	on:click
	on:mouseenter
	on:mouseleave
	on:keyup
	on:keydown
	class="{circle ? 'rounded-full' : ''} relative  focus-within:ring-0 ${!noShadow
		? 'shadow-lightNormal dark:shadow-darkNormal cursor-pointer'
		: ''}  {className}"
>
	{#if badge}
		<Badge color={badgeColor} class="absolute bottom-3/4 left-1/2 rounded-full">{badgeTxt}</Badge>
	{/if}
	<div class="flex items-center justify-center position-relative">
		<Loader bind:loading>
			<slot />
		</Loader>
	</div>
</Button>
