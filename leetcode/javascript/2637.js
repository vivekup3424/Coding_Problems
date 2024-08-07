/**
 * @param {Function} fn
 * @param {number} t
 * @return {Function}
 */
//var timeLimit = function (fn, t) {
//  return async function (...args) {
//    return new Promise((resolve, reject) => {
//      setTimeout(() => {
//        return reject("Time Limit Exceeded");
//      }, t);
//      fn(...args)
//        .then((response) => resolve(response))
//        .catch((err) => reject(err));
//    });
//  };
//};

var timeLimit = function (fn, t) {
  return async function (...args) {
    return new Promise((resolve, reject) => {
      const id = setTimeout(() => {
        return reject("Time Limit Exceeded");
      }, t);
      fn(...args)
        .then((response) => resolve(response))
        .catch((err) => reject(err))
        .finally(() => clearTimeout(id));
    });
  };
};
/**
 * const limited = timeLimit((t) => new Promise(res => setTimeout(res, t)), 100);
 * limited(150).catch(console.log) // "Time Limit Exceeded" at t=100ms
 */
