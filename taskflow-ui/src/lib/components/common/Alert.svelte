<script lang="ts">
	import { spring } from 'svelte/motion';
	import { onMount, onDestroy } from 'svelte';
	import { Alert } from 'flowbite-svelte';
	import { Info, CheckCircle, AlertTriangle, XCircle } from 'lucide-svelte';
	import { alertStore } from '$lib/utils/alertStore';

	let message = '';
	let type: 'success' | 'error' | 'info' | 'warning' = 'info';
	let duration = 2000;
	let visible = false;

	const springMotion = spring(
		{ x: 10 },
		{
			stiffness: 0.3,
			damping: 0.7
		}
	);

	let timer: NodeJS.Timeout;

	$: if ($alertStore.visible) {
		({ message, type, duration } = $alertStore);
		showAlert();
	}

	function showAlert() {
		visible = true;
		springMotion.set({ x: 0 });

		clearTimeout(timer);
		timer = setTimeout(() => {
			springMotion.set({ x: 10 });
			setTimeout(() => {
				visible = false;
			}, 300);
		}, duration);
	}

	onDestroy(() => {
		clearTimeout(timer);
	});

	const alertColors = {
		success: 'green',
		error: 'red',
		warning: 'yellow',
		info: 'blue'
	};

	const icons = {
		success: CheckCircle,
		error: XCircle,
		warning: AlertTriangle,
		info: Info
	};
</script>

{#if visible}
	<div
		class="fixed top-4 z-50 transition-transform duration-300 ease-in-out"
		style="left:45%;"
	>
		<Alert
			color={alertColors[type]}
			class="rounded-full shadow-lg border border-{alertColors[
				type
			]}-200 bg-opacity-90 backdrop-blur-sm"
		>
			<svelte:component this={icons[type]} slot="icon" size={24} class="flex-shrink-0" />
			<span class="font-medium text-sm ml-2">{message}</span>
		</Alert>
	</div>
{/if}