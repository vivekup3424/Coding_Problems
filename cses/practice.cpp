#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
int main() { ; }
class Solution {
public:
  vector<vector<int>> findDifference(vector<int> &nums1, vector<int> &nums2) {
    unordered_set<int> s1{begin(nums1), end(nums1)};
    unordered_set<int> s2{begin(nums2), end(nums2)};
    vector<vector<int>> ans(2);
    for (const int n : s1)
      if (!s2.count(n))
        ans[0].push_back(n);
    for (const int n : s2)
      if (!s1.count(n))
        ans[1].push_back(n);

    return ans;
  }
};
