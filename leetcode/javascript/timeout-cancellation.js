/**
 * @param {Function} fn
 * @param {Array} args
 * @param {number} t
 * @return {Function}
 */
var cancellable = function(fn,args,t){
    const id = setTimeout(() => {
        fn(...args)
    }, t);
    var cancelFn = function(){
        clearTimeout(id);
    }
    return cancelFn;
}