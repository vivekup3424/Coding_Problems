#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int getMinDiff(vector<int> &arr, int k) {
      int maxi = *max_element(arr.begin(), arr.end());
      int mini = *min_element(arr.begin(), arr.end());
      return maxi - mini + 2 *k;
    }
};