/**
 * @param {number}n
 * @param {Function}counter
 */
var createCounter = function(n){
    let value = n;
    return function(){
        return value++
    }
}