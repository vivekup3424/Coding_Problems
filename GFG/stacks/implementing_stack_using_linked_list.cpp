//implementing stack using linked list

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
class Node{
public:
  int data;
  Node *next;
  Node(int _val):data(_val),next(nullptr){};
};
class Stack{
public:
  Node *top;
  Stack():top(nullptr){} //abusing initializer list
  int pop(){
    //removes element from the stack and returns it
    //NOTE:- error = -1
    try {
    if(top==nullptr){
        throw std::runtime_error("Stack Empty: Can't remove element it (⊙_☉)");
      }
      int data = top->data;
      Node *nextNode = top->next;
      delete top;
      top = nextNode;
      return data;
    } catch (std::exception &e) {
      std::cout<<e.what()<<std::endl;
      return -1;
    }
  }
  void push(int _val){
    Node *newNode = new Node(_val);
    newNode->next = top;
    top = newNode;
  }
  ~Stack(){
    while(top!=nullptr){
      auto nextNode = top->next;
      delete top;
      top = nextNode;
    }
  }
};
