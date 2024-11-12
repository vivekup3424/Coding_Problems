#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
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

  int pop() {
    // Removes the top element and returns it
    try {
      if (topIdx < 0) {
        throw std::runtime_error(
            "Can't get a top element from an empty stack, can we?");
      }
      auto temp = arr[topIdx];
      topIdx--;
      return temp;
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      return -1;
    }
  }

  bool push(int x) {
    //adds an element to the stack
    try {
      if (topIdx + 1 == MAX_SIZE) {
        throw std::runtime_error(
            "Can't insert into a stack, which is already full, can we?");
      }
      topIdx++;
      arr[topIdx] = x;
      return true;
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      return false;
    }
  }
  int front() {
    // shows the top element if its exists, else return -1 and err
    try {
      if (topIdx < 0) {
        throw std::runtime_error("Can show top element from an empty stack\n");
      }
      return arr[topIdx];
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      return -1; // return an error -1 to symbolise error
    }
  }
  ~Stack() { free(arr); }
};
