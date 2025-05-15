<script lang="ts">
    import { Button, Modal } from "flowbite-svelte";

    export let title = "";
    export let open = false;
    let className = ""
    export {className as class}
</script>


    <Modal class="{className} border-black border-2" {title} bind:open autoclose outsideclose>
        <slot />
    </Modal>
