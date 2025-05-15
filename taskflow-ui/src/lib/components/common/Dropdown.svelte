 <script lang="ts">
    import { Dropdown, DropdownItem } from 'flowbite-svelte';
    import { ChevronDown } from 'lucide-svelte';
    import { createEventDispatcher, onMount } from 'svelte';
    import Button from './Button.svelte';
    import { truncateText } from '$lib/utils';
    import Checkbox from './Checkbox.svelte';

    export let list: any[];
    export let filterField = "";
    export let noShadow = false;
    export let disabled = false;
    export let showCheckbox = false;
    export let heading: any = 'Filter';
    export let headingDirection: 'left' | 'right' | 'center' = 'left';
    let className = '';
    export { className as class };
	export let DropdownItemClass = '';
    export let showChevronDownIcon = true;

    let filterList: any[] = [];
    let buttonElement: HTMLElement;
    let dropdownWidth: string;

    $: filterList = filterField ? list.map((l) => l[filterField]) : list;

    let isOpen = false;
    let checkboxes: boolean[] = [];
    let isList = false;
    let filterCount = 0;
    const dispatch = createEventDispatcher();

    onMount(() => {
        if (buttonElement) {
            dropdownWidth = `${buttonElement.offsetWidth}px`;
        }
    });

    const clicked = (index: number) => {
        if (showCheckbox) {
            if (checkboxes[index]) filterCount--;
            else filterCount++;
            checkboxes = checkboxes.map((val, i) => (i == index ? !val : val));
        } else {
            isOpen = false;
            checkboxes = checkboxes.map((val, i) => (index == i ? val : false));
            checkboxes[index] = true;
            heading = filterList[index];
        }
        dispatch('clickItem', { item: list[index], index, selectedItems: list.filter((val, i) => checkboxes[i]) });
        handleFilterCount();
    };

    const handleClearAllFilter = () => {
        checkboxes = checkboxes.map(val => false);
        filterCount = 0;
        dispatch("clearAll");
        handleFilterCount();
    };

    const handleFilterCount = () => {
        dispatch("handleFilterCount", { count: filterCount });
    };

    $: {
        if (list.length && !isList) {
            checkboxes = list.map(l => false);
            isList = true;
        }
    }

    $: if (buttonElement && isOpen) {
        dropdownWidth = `${buttonElement.offsetWidth}px`;
    }
</script>

<div class="relative" bind:this={buttonElement}>
    <Button color="none" {disabled} class="dark:bg-templateDarkClr dark:shadow-boxShadow flex justify-{headingDirection=='center' ? 'center' : headingDirection=='left' ? 'start' : 'end'} {className}">
        <span class="overflow-hidden text-nowrap flex-1 dark:text-dark">{truncateText(heading, 20)}</span>
        <ChevronDown class="dark:text-dark h-4 w-4 ms-2 dark:bg-templateDarkClr {showChevronDownIcon ? "" : "hidden"}" />
    </Button>

    <Dropdown 
        bind:open={isOpen} 
        classContainer="max-h-48 overflow-y-auto"
        style="min-width: {dropdownWidth}"
    >
        {#if showCheckbox}
            <DropdownItem on:click={handleClearAllFilter} defaultClass="cursor-pointer flex my-2 px-3">
                Clear All
            </DropdownItem>
        {/if}
        {#each filterList as item, index}
            <DropdownItem 
                defaultClass="cursor-pointer flex my-2 px-3 {DropdownItemClass} flex justify-{headingDirection=='center' ? 'center' : headingDirection=='left' ? 'start' : 'end'} {showCheckbox ? 'justify-between' : ''}" 
                on:click={() => clicked(index)}
            >
                {item}
                {#if showCheckbox}
                    <span class="cursor-pointer">
                        <Checkbox bind:checked={checkboxes[index]} />
                    </span>
                {/if}
            </DropdownItem>
        {/each}
    </Dropdown>
</div>

<!-- <div class="relative" bind:this={buttonElement}>
    <Button color="none" {disabled} class="dark:bg-templateDarkClr dark:shadow-boxShadow flex justify-{headingDirection=='center' ? 'center' : headingDirection=='left' ? 'start' : 'end'} {className}">
        <span class="overflow-hidden text-nowrap flex-1 dark:text-dark">{truncateText(heading, 20)}</span>
        <ChevronDown class="dark:text-dark h-4 w-4 ms-2 dark:bg-templateDarkClr {showChevronDownIcon ? "" : "hidden"}" />
    </Button>

    <Dropdown 
        bind:open={isOpen} 
        classContainer="max-h-48 overflow-y-auto scrollbar-thin scrollbar-thumb-gray-300 scrollbar-track-gray-100 hover:scrollbar-thumb-gray-400"
        style="min-width: {dropdownWidth}"
    >
        {#if showCheckbox}
            <DropdownItem on:click={handleClearAllFilter} defaultClass="cursor-pointer flex my-2 px-3">
                Clear All
            </DropdownItem>
        {/if}
        {#each filterList as item, index}
            <DropdownItem 
                defaultClass="cursor-pointer flex my-2 px-3 {DropdownItemClass} flex justify-{headingDirection=='center' ? 'center' : headingDirection=='left' ? 'start' : 'end'} {showCheckbox ? 'justify-between' : ''}" 
                on:click={() => clicked(index)}
            >
                {item}
                {#if showCheckbox}
                    <span class="cursor-pointer">
                        <Checkbox bind:checked={checkboxes[index]} />
                    </span>
                {/if}
            </DropdownItem>
        {/each}
    </Dropdown>
</div>

<style>
/* Modern scrollbar styling */
:global(.scrollbar-thin)::-webkit-scrollbar {
    width: 6px;
}

:global(.scrollbar-thin)::-webkit-scrollbar-track {
    background: #f1f1f1;
    border-radius: 3px;
}

:global(.scrollbar-thin)::-webkit-scrollbar-thumb {
    background: #d1d5db;
    border-radius: 3px;
}

:global(.scrollbar-thin)::-webkit-scrollbar-thumb:hover {
    background: #9ca3af;
}

/* For Firefox */
:global(.scrollbar-thin) {
    scrollbar-width: thin;
    scrollbar-color: #d1d5db #f1f1f1;
}
</style> -->
