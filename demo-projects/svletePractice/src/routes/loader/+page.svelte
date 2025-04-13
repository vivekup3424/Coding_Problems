<style>
    :global(body){
        background-color: #000;
        color: yellow;
        font-family: 'Comic Sans MS', 'Sans-serif';
        font-size: 2rem;
        height: 100vh;
        width: 100vw;
        justify-content: center;
        align-items: center;
    }
    button{
        width: 50%;
        font-size: 4rem;
    }
</style>

<script>
    import {counter} from "$lib/shared.svelte"
    const increment = () =>{
        counter.count = counter.count + 1
    }
</script>

<button onclick={increment}>
    {counter.count}
</button>

