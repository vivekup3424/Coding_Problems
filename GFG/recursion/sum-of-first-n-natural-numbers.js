const readline = require("readline");
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
const calculateSum = (n) => {
  if (n == 0) {
    return 0;
  } else {
    return n + calculateSum(n - 1);
  }
};
let n = 0;
rl.question("Enter a number n", (n) => {
  process.stdout.write(
    `The sum of first ${n} natural numbers is ${calculateSum(n)}`,
  );
});
