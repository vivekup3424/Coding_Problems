#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

class Stack {
private:
    int MAX_SIZE;
    int topIdx;
    int *arr;

public:
    Stack(int size) : MAX_SIZE(size), topIdx(-1) {
        arr = (int *)malloc(size * sizeof(int));
    }

    ~Stack() { free(arr); }

    bool push(int x) {
        // Adds an element to the stack
        try {
            if (topIdx + 1 == MAX_SIZE) {
                throw std::runtime_error("Stack is full!");
            }
            arr[++topIdx] = x;
            return true;
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    int pop() {
        // Removes the top element and returns it
        try {
            if (topIdx < 0) {
                throw std::runtime_error("Stack is empty!");
            }
            return arr[topIdx--];
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            return -1;
        }
    }

    int front() {
        // Shows the top element if it exists
        try {
            if (topIdx < 0) {
                throw std::runtime_error("Stack is empty!");
            }
            return arr[topIdx];
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            return -1;
        }
    }

    int getSum() const {
        // Returns the sum of all elements in the stack
        int sum = 0;
        for (int i = 0; i <= topIdx; ++i) {
            sum += arr[i];
        }
        return sum;
    }
};

// Game function
void playGame() {
    const int stackSize = 5;
    Stack stack(stackSize);
    int target = rand() % 50 + 1;  // Random target between 1 and 50
    int choice;

    std::cout << "Welcome to the Stack Challenge!\n";
    std::cout << "Try to reach the target score by pushing or popping numbers.\n";
    std::cout << "Target Score: " << target << "\n\n";

    while (true) {
        std::cout << "Current Stack Sum: " << stack.getSum() << "\n";
        std::cout << "Top Element: " << stack.front() << "\n";
        std::cout << "Choose an action:\n";
        std::cout << "1. Push a number\n";
        std::cout << "2. Pop the top number\n";
        std::cout << "3. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int num;
            std::cout << "Enter a number to push: ";
            std::cin >> num;
            if (stack.push(num)) {
                std::cout << num << " pushed onto the stack.\n";
            } else {
                std::cout << "Push failed. Stack might be full.\n";
            }
        } else if (choice == 2) {
            int poppedValue = stack.pop();
            if (poppedValue != -1) {
                std::cout << "Popped " << poppedValue << " from the stack.\n";
            }
        } else if (choice == 3) {
            std::cout << "Thanks for playing!\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }

        // Check if the player has matched or exceeded the target score
        int currentSum = stack.getSum();
        if (currentSum == target) {
            std::cout << "Congratulations! You reached the target score of " << target << "!\n";
            break;
        } else if (currentSum > target) {
            std::cout << "Oops! Your score exceeded the target. Try popping some numbers.\n";
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Seed for random target generation
    playGame();
    return 0;
}

