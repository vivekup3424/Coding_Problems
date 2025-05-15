<script>
    import { Input } from 'flowbite-svelte';
    import { Search } from 'lucide-svelte';
    export let placeholder = '';
    export let value = ""
    let className = "";
    export {className as class}
</script>
<div class="relative max-w-[70%] flex-grow {className}">
    <div class="flex absolute inset-y-0 start-0 items-center ps-3 pointer-events-none">
        <Search class="w-4 h-4 text-grey dark:text-white"/>
    </div>
    <Input on:input bind:value id="search-navbar" class="ps-10 bg-templateClr" placeholder="Search..." />
</div>