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
    stack<int> st;
    st.push(-1);
    int max_len = 0;

    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '(') {
        st.push(i);
      } else {
        st.pop();
        if (st.empty()) {
          st.push(i);
        } else {
          max_len = max(max_len, i - st.top());
        }
      }
    }

    return max_len;
  }
};
int main(int argc, char *argv[]) {
  freopen("~/Desktop/fileInput.txt", "r", stdin);
  string s;
  cin >> s;
  cout << Solution().maxLength(s);
  return 0;
}
