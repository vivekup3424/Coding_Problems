<script lang="ts">
	export let size: 'sm' | 'md' | 'lg' = 'md';
	export let color: string = 'text-blue-600';
	
	// Compute classes based on size
	$: sizeClass = {
	  'sm': 'w-4 h-4',
	  'md': 'w-8 h-8',
	  'lg': 'w-12 h-12'
	}[size];
  </script>
  
  <div class="flex justify-center items-center">
	<div class="{sizeClass} {color} animate-spin rounded-full border-2 border-solid border-current border-r-transparent" role="status">
	  <span class="sr-only">Loading...</span>
	</div>
  </div>