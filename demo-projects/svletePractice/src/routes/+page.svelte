<script lang="ts">
    let count = $state(0);
    function incrementCount(){
        count++;
    }
</script>
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
       left: 50%;
       width: 50%;
       font-size: 4rem;
    }
</style>
<p>If you press this below button, something magical might happen</p>
<button onclick={incrementCount}>Click Me: {count}</button>