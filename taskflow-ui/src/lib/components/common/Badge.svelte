<script lang="ts">
	type colorType = 'white' | 'red' | 'blue' | 'black' | 'plain';
	export let badgeColor: colorType;
	export let badgeTxt = '';
</script>

<div
	class="badge-{badgeColor} d-flex flex-column align-items-center justify-content-center {badgeTxt
		? 'px-1 pt-0 pb-0'
		: ''}"
>
	{badgeTxt}
</div>
