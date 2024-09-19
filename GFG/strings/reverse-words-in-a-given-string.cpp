#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
void swapString(string &str, int l, int r) {
  while (l < r) {
    swap(str[l++], str[r--]);
  }
}
string reverseWords(string str) {
  int n = str.size();
  int l = 0, r = n - 1;
  swapString(str, l, r);
  l = 0, r = 0;
  while (r < n) {
    while (r < n and str[r] == '.') {
      r++;
    }
    l = r;
    while (r < n and str[r] != '.') {
      r++;
    }
    if (r - l > 1) {
      swapString(str, l, r - 1);
      l = r;
    }
  }
  return str;
}
