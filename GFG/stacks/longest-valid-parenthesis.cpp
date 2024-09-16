#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
/**
 * Given a string str consisting of opening and closing parenthesis '(' and ')'.
 * Find length of the longest valid parenthesis substring.
 * A parenthesis string is valid if:
 * For every opening parenthesis, there is a closing parenthesis.
 * Opening parenthesis must be closed in the correct order.
 */
// )()())
class Solution {
public:
  int maxLength(string s) {
    stack<int> stk;
    int maxi = 0;
    for (char c : s) {
      if (c == '(') {
        stk.push(-1);
      } else if (c == ')') {
        int temp = 0;
        while (stk.size() > 0 && stk.top() != 0 && stk.top() != -1) {
          auto i = stk.top();
          stk.pop();
          temp += i;
        }
        if (stk.size()>0 && stk.top() == -1) {
          stk.pop();
          temp += 2;
        }
        maxi = max(maxi,temp);
        stk.push(temp);
      }
    }
    //empty up the stack
    while(stk.size()>0){
      auto s = 0;
      while(stk.size()>0 and stk.top()>0){
        s += stk.top();
        stk.pop();
      }
      if(stk.size()>0){
        stk.pop();
      }
      maxi = max(maxi,s);
    }
    return maxi;
  }
};
int main (int argc, char *argv[]) {
  freopen("~/Desktop/fileInput.txt",  "r", stdin);
  string s;
  cin>>s;
  cout<<Solution().maxLength(s);
  return 0;
}
