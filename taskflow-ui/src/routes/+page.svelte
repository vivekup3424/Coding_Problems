<script lang="ts">
	import TaskflowList from "$lib/components/TaskflowList.svelte";
	import TemplateList from "$lib/components/TemplateList.svelte";
	import TemplatePopup from "$lib/components/TemplatePopup.svelte";
	import TemplateModal from "$lib/components/TemplateModal.svelte";
	import TaskflowModal from "$lib/components/TaskflowModal.svelte";
	import { templateActions } from "$lib/stores/template";
	import Loader from "$lib/components/common/Loader.svelte";
	import { onMount } from "svelte";
	import { TaskflowApiCaller } from "$lib/api/taskflow";
    import type { ITask } from "$lib/types/taskflow";
    import { taskflowActions } from "$lib/stores/taskflow";
    import { TaskflowApi } from "$lib/api/taskflow-api";
    import type { Template } from "$lib/types/template";
    import Button from "$lib/components/common/Button.svelte";
    import { refreshData } from "$lib/stores";

	let activeTab: "taskflows" | "templates" = "taskflows";
	let showTemplateModal = false;
	let showNewTaskflowModal = false;
	let templateLoading = false;
	let taskflowLoading = false;
	let loading = false
	let selectedTemplate: Template | null = null;
	let templateModalMode: 'create' | 'update' = 'create';

	function handleAddNewClick() {
		// if (activeTab === "taskflows") {
		// 	showNewTaskflowModal = true;
		// } else {
		// 	templateModalMode = 'create';
		// 	selectedTemplate = null;
		// 	showTemplateModal = true;
		// }
		if (activeTab === "taskflows") {
			showNewTaskflowModal = true;
		} else {
			templateModalMode = 'create';
			selectedTemplate = null;  // This is important to reset the template
			showTemplateModal = true;
		}
	}

	function handleCloseNewTemplateModal() {
		// showTemplateModal = false;
		showTemplateModal = false;
		if (templateModalMode === 'create') {
			selectedTemplate = null;
		}
	}

	function handleCloseNewTaskflowModal() {
		showNewTaskflowModal = false;
	}

	const handleCreateTemplate = async () => {
		templateLoading = true;
		await templateActions.fetchTemplates();
		templateLoading = false;
	};

	const handleUpdateTemplate = async () => {
		loading = true;
		await templateActions.fetchTemplates();
		loading = false;
	};

	const handleTemplateUpdate = (event: CustomEvent) => {
		selectedTemplate = event.detail;
		templateModalMode = 'update';
		showTemplateModal = true;
	};

	const handleCreateTaskflow = async () => {
		loading = true;
		await taskflowActions.fetchTaskflows();
		loading = false;
	}

	const handleRefresh = async () => {
		if(activeTab == "taskflows") loading = true
		else loading = true
		
		await refreshData();

		if(activeTab == "taskflows") loading = false
		else loading = false
	}


</script>

<svelte:head>
	<title>Taskflow Management</title>
</svelte:head>

<div class="flex flex-col h-screen">
	<!-- Fixed header section -->
	<div class="p-6 bg-white">
		<div class="flex justify-between items-center mb-6">
			<h1 class="text-2xl font-bold text-gray-800">
				Taskflow Management
			</h1>
			<div class="flex space-x-2">
				<Button
					on:click={handleAddNewClick}
					class="px-4 py-2 bg-blue-600 text-white text-sm font-medium rounded-md"
				>
					Add New {activeTab === "taskflows"
						? "Taskflow"
						: "Template"}
				</Button>
				<Button
					on:click={handleRefresh}
					class="px-4 py-2 border border-gray-300 bg-white text-sm font-medium rounded-md text-gray-700"
				>
					Refresh
			</Button>
			</div>
		</div>

		<!-- Dashboard Tabs -->
		<div class="border-b border-gray-200">
			<nav class="flex -mb-px">
				<Button
					on:click={() => (activeTab = "taskflows")}
					class={`py-4 px-6 text-center border-b-2 font-medium text-sm ${activeTab === "taskflows" ? "border-blue-500 text-blue-600" : "border-transparent text-gray-500"}`}
				>
					Taskflows
				</Button>
				<Button
					on:click={() => (activeTab = "templates")}
					class={`py-4 px-6 text-center border-b-2 font-medium text-sm ${activeTab === "templates" ? "border-blue-500 text-blue-600" : "border-transparent text-gray-500"}`}
				>
					Templates
				</Button>
			</nav>
		</div>
	</div>

	<div class="flex-1 overflow-auto p-6 pt-0">
		<Loader class="h-full flex items-center justify-center" bind:loading>
			{#if activeTab === "taskflows"}
				<TaskflowList />
			{:else}
				<TemplateList on:updateTemplate={handleTemplateUpdate} />
			{/if}
		</Loader>
	</div>

	<TemplatePopup />

	<TemplateModal
		bind:show={showTemplateModal}
		mode={templateModalMode}
		template={selectedTemplate}
		on:createTemplate={handleCreateTemplate}
		on:updateTemplate={handleUpdateTemplate}
		on:close={handleCloseNewTemplateModal}
	/>

	<TaskflowModal
		on:createTemplate={handleCreateTaskflow}
		show={showNewTaskflowModal}
		on:close={handleCloseNewTaskflowModal}
	/>
</div>