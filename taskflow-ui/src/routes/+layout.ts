import { init } from "$lib"
import type { LayoutLoad } from "./$types"
import { browser } from '$app/environment';
import { taskflowActions } from "$lib/stores/taskflow";
import { templateActions } from "$lib/stores/template";

// export const ssr = false

export const load: LayoutLoad = async ({ params }) => {
	if(browser){
		await init();
		await taskflowActions.fetchTaskflows();
		await templateActions.fetchTemplates();
	}

}
