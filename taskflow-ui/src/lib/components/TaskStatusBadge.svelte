<script lang="ts">
	import { TaskStatus } from '$lib/types/taskflow';
	
	export let status: TaskStatus = TaskStatus.WAITING;
	
	$: bgColor = getBgColor(status);
	$: textColor = getTextColor(status);
	
	function getBgColor(status: TaskStatus): string {
	  switch (status) {
		case TaskStatus.SUCCESS: return 'bg-green-100';
		case TaskStatus.RUNNING: return 'bg-yellow-100';
		case TaskStatus.FAILED: return 'bg-red-100';
		case TaskStatus.WAITING: return 'bg-gray-100';
		case TaskStatus.QUEUED: return 'bg-blue-100';
		default: return 'bg-gray-200';
	  }
	// return ""
	}
	
	function getTextColor(status: TaskStatus): string {
	  switch (status) {
		case TaskStatus.SUCCESS: return 'text-green-800';
		case TaskStatus.RUNNING: return 'text-yellow-800';
		case TaskStatus.FAILED: return 'text-red-800';
		case TaskStatus.WAITING: return 'text-gray-800';
		case TaskStatus.QUEUED: return 'text-blue-800';
		default: return 'text-gray-700';
	  }
	}
  </script>
  
  <span class="inline-flex items-center px-2 py-1 rounded-full text-xs font-medium {bgColor} {textColor}">
	{status}
  </span> 