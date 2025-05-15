<script lang="ts">
	import { StageStatus, TaskflowStatus, TaskStatus } from '$lib/types/taskflow';
	
	export let status: TaskflowStatus | StageStatus | TaskStatus = TaskflowStatus.WAITING;
	
	$: bgColor = getBgColor(status);
	$: textColor = getTextColor(status);
	
	function getBgColor(status: TaskflowStatus): string {
	  switch (status) {
		case TaskflowStatus.COMPLETED: return 'bg-green-100';
		case TaskflowStatus.RUNNING: return 'bg-yellow-100';
		case TaskflowStatus.CANCELLED: return 'bg-red-100';
		case TaskflowStatus.PARTIAL_COMPLETED: return 'bg-orange-100';
		case TaskflowStatus.WAITING: return 'bg-gray-100';
		case TaskflowStatus.FAILED: return 'bg-red-100';
		default: return 'bg-gray-200';
	  }
	}
	
	function getTextColor(status: TaskflowStatus): string {
	  switch (status) {
		case TaskflowStatus.COMPLETED: return 'text-green-800';
		case TaskflowStatus.RUNNING: return 'text-yellow-800';
		case TaskflowStatus.CANCELLED: return 'text-red-800';
		case TaskflowStatus.PARTIAL_COMPLETED: return 'text-orange-800';
		case TaskflowStatus.WAITING: return 'text-gray-800';
		case TaskflowStatus.FAILED: return 'text-red-800';
		default: return 'text-gray-700';
	  }
	}
  </script>
  
  <span class="inline-flex items-center px-2 py-1 rounded-full text-xs font-medium {bgColor} {textColor}">
	{status}
  </span>