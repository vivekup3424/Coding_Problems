//implementing stack using array
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>
class Stack{
private:
  int MAX_SIZE;
  int topIdx;
  int *arr;
public:
  Stack(int size): MAX_SIZE(size), topIdx(-1){
    arr = (int *)malloc(size * sizeof(int));
  }
  ~Stack(){
    free arr;
  }
  int pop(){
    //removes the top element and returns it
    try {
    if(topIdx < 0){
        throw std::runtime_error("Can't get a top element from an empty stack, can we?");
    }
    auto temp = arr[topIdx];
    topIdx--;
    return temp;
    } catch (std::exception e) {
      std::cout<<e.what()<<std::endl;
      return -1;
    }
  }
  bool push(int x)
    try {
    if(topIdx+1 == MAX_SIZE){
        throw std::runtime_error("Can't insert into a stack, which is already full, can we?");
      }
      topIdx++;
      arr[topIdx] = x;
      return arr[topIdx];
    } catch (std::exception e) {
      std::cout<<e.what()<<std::endl;
      return -1;
    }
  }
};
