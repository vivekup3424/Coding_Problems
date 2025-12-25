/**
 * @param {integer} init
 * @return { increment: Function, decrement: Function, reset: Function }
 */
var createCounter = function(init) {
    let val = init
    function increment(){
        val++
        return val
    }
    function decrement(){
        val--
        return val
    }
    function reset(){
        val = init
        return val
    }
    return [increment,decrement,reset]
};

/**
 * const counter = createCounter(5)
 * counter.incremen t(); // 6
 * counter.reset(); // 5
 * counter.decrement(); // 4
 */