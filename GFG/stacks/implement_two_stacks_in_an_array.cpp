#include <bits/stdc++.h>
using namespace std;

class AbstractExample{
public:  // Access specifier should be public for the interface
  virtual void push1(int x) = 0;
  virtual void push2(int x) = 0;
  virtual int pop1() = 0;
  virtual int pop2() = 0;
  virtual ~AbstractExample() {}  // Virtual destructor for proper cleanup
};

class TwoStacks: public AbstractExample{
private:
  vector<int> elements;
  int pointerLeft;
  int pointerRight;
  
public:  // Constructor should be public
  TwoStacks(){
    elements.resize(100,0);
    pointerLeft=-1;
    pointerRight=100;
  }
  
  bool isArrayFull(){
    return pointerLeft + 1 == pointerRight;  // Fixed condition
  }
  
  void push1(int x) override {  // Implementing interface methods
    if(isArrayFull()){
      return;
    }
    pointerLeft++;
    elements[pointerLeft] = x;
    return;
  }
  
  void push2(int x) override {
    if(isArrayFull()){
      return;
    }
    pointerRight--;
    elements[pointerRight] = x;
    return;
  }
  
  int pop1() override {
    if(pointerLeft == -1){
      return -1;
    }
    int value = elements[pointerLeft];  // Get the value first
    pointerLeft--;
    return value;
  }
  
  int pop2() override {
    if(pointerRight == 100){
      return -1;
    }
    int value = elements[pointerRight];  // Get the value first
    pointerRight++;
    return value;
  }
};
