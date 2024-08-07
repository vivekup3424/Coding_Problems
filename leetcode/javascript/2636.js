/**
 * @param {Function{}} functions
 * @param {number} n
 * @return {Function}
 */

var promisePool = async function (functions, n) {
  //n - is the promise pool size
  return new Promise((resolve, reject) => {});
};

const sleep = (t) => new Promise((resolve) => setTimeout(resolve, t));
promisePool([() => sleep(500), () => sleep(400)], 1).then(
  console.log("promise pool completed")
);
