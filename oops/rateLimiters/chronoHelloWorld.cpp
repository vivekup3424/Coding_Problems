#include <chrono>   // For high-resolution time measurement
#include <iostream> // For standard I/O operations
#include <ostream>  // Included to support << operator in standard output

long Fibonacci(unsigned n) {
    return n < 2 ? n : Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main() {
    const auto start = std::chrono::steady_clock::now();
    const auto fb = Fibonacci(42);
    const auto end = std::chrono::steady_clock::now();
    // Calculate the elapsed time in milliseconds by subtracting start from end
    // and casting the result to milliseconds
    const auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Fibonacci(42): " << fb << std::endl;
    std::cout << "Elapsed time: " << elapsed_milliseconds.count() << " ms" << std::endl;
    return 0;
}
