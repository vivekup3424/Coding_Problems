/**
 * Design a stack with the following operations.

    push(Stack s, x): Adds an item x to stack s 
    pop(Stack s): Removes the top item from stack s 
    merge(Stack s1, Stack s2): Merge contents of s2 into s1.
*/

#include <bits/stdc++.h>
#include <exception>
#include <stdexcept>
using namespace std;

class Node{
public:
  int data;
  Node *next;
  Node(int _val){
    data = _val;
    next = nullptr;
  }
};
//implementing stack with linkedlist
class Stack{
public:
  Node *front;
  Node *back;
  Stack(){
    top = nullptr;
  }
  void push(int _val){
    auto newNode = new Node(_val);
    newNode->next = top;
    top = newNode;
  }
  int pop(){
    try {
    if(top==nullptr){
        throw runtime_error("Cannot pop from an empty stack. ∧＿∧ \\/");
      }
    auto temp = top->data;
    auto nextNode = top->next;
    delete top;
    top = top->next;
    return temp;
    } catch (const exception &e) {
      cout<<e.what()<<endl;
      return -1;
    }
  }
};

void merge(Stack &s1, Stack &s2){
  //merge s2 into s1
  auto t1 = s1.top, t2 = s2.top;
  if(t1==nullptr){
    s1 = s2;
  }else{
    
  }
}
