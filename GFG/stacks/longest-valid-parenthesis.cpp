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
    stack<string> stk;
    int maxi = 0;
    for (char c : s) {
      if (c == '(') {
        stk.push("(");
      } else if (c == ')') {
        int temp = 0;
        while (stk.size() > 0 && stk.top() != "0" && stk.top() != "(") {
          auto t = stk.top();
          stk.pop();
          auto i = stoi(t);
          temp += i;
        }
        if (stk.size()>0 && stk.top() == "(") {
          stk.pop();
          temp += 2;
        }
        maxi = max(maxi,temp);
        stk.push(to_string(temp));
      }
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
