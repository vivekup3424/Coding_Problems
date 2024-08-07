/**
 * @param {Function{}} functions
 * @param {number} n
 * @return {Function}
 */

var promisePool = async function (functions, n) {
  //n - is the promise pool size
  return new Promise((resolve, reject) => {
    let i = 0;
    let inProgress = 0;
    while (i < functions.length() && i < n) {
      functions[i++]().then(callback);
      inProgress++;
    }

    function callback() {
      inProgress--;
      if (i == functions.length && inProgress == 0) {
        resolve();
      }
      functions[i](); //closure
    }
  });
};

const sleep = (t) => new Promise((resolve) => setTimeout(resolve, t));
promisePool([() => sleep(500), () => sleep(400)], 1).then(
  console.log("promise pool completed")
);
