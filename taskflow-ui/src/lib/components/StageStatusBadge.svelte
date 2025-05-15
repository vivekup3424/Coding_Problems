<script lang="ts">
	import { StageStatus } from '$lib/types/taskflow';
	
	export let status: StageStatus = StageStatus.WAITING;
	
	$: bgColor = getBgColor(status);
	$: textColor = getTextColor(status);
	
	function getBgColor(status: StageStatus): string {
	//   switch (status) {
	// 	case StageStatus.COMPLETED: return 'bg-green-100';
	// 	case StageStatus.RUNNING: return 'bg-yellow-100';
	// 	case StageStatus.FAILED: return 'bg-red-100';
	// 	case StageStatus.WAITING: return 'bg-gray-100';
	// 	case StageStatus.PARTIAL_COMPLETED: return "bg-orange-100"
	// 	default: return 'bg-gray-200';
	//   }
	return "";
	}
	
	function getTextColor(status: StageStatus): string {
	  switch (status) {
		case StageStatus.COMPLETED: return 'text-green-800';
		case StageStatus.RUNNING: return 'text-yellow-800';
		case StageStatus.FAILED: return 'text-red-800';
		case StageStatus.WAITING: return 'text-gray-800';
		case StageStatus.PARTIAL_COMPLETED: return "text-orange-800"
		default: return 'text-gray-700';
	  }
	}
  </script>
  
  <span class="inline-flex items-center px-2 py-1 rounded-full text-xs font-medium {bgColor} {textColor}">
	{status}
  </span> 