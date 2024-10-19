#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int constrainedSubsetSum(vector<int> &nums, int k) {
    int n = nums.size();
    vector<int> dp(n, 0);
    int maxi = INT_MIN;
    for (int i = 0; i < n; i++) {
      if (i == 0) {
        dp[i] = nums[i];
      } else {
        int c = INT_MIN;
        for (int j = i - 1; j >= max(0, i - k); j--) {
          c = max(c, dp[j]);
        }
        dp[i] = c + nums[i];
      }
      maxi = max(maxi, dp[i]);
    }
    return dp[n - 1];
  }
};
