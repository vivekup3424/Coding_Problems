import readline from "readline";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Function to print numbers from i to n recursively
function print1toN(i, n) {
  if (i === n) {
    process.stdout.write(`${i} `); // Inline output
    return;
  }
  process.stdout.write(`${i} `); // Inline output
  print1toN(i + 1, n);
}

// Single input prompt for simplicity
rl.question("Enter the starting and ending numbers (e.g., 1 5): ", (input) => {
  const [i, n] = input.split(" ").map(Number); // Parse input into numbers
  if (isNaN(i) || isNaN(n) || i > n) {
    console.log(
      "Invalid input! Please enter two numbers where the first is <= second.",
    );
  } else {
    // Print numbers from i to n
    console.log([...Array(n - i + 1).keys()].map((k) => k + i).join(" "));
  }
  rl.close(); // Close the interface
});
