#include <bits/stdc++.h>
#include <cctype>
using namespace std;

// function to decide the precendence of operators
int precedence(char c) {
  if (c == '^') {
    return 3;
  } else if (c == '*' || c == '/') {
    return 2;
  } else if (c == '+' || c == '-') {
    return 1;
  } else {
    return 0;
  }
}
void infixToPostFix(string &s) {
  stack<char> stk;
  string result;
  for (char c : s) {
    if (isalnum(c)) {
      result += c;
    } else if (c == '(') {
      stk.push(c);
    } else if (c == ')') {
      while (stk.top() != '(') {
        result += stk.top();
        stk.pop();
      }
      stk.pop();
    } else {
      stk.push(c);
    }
  }
  while (stk.size() > 0) {
    result += stk.top();
    stk.pop();
  }
  cout << result << endl;
}
int main(){
  string operations = "((1 + 2) - (3 / 5))";
  infixToPostFix(operations);
}
