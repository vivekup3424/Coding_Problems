#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int countCompleteSubarrays(vector<int> &nums) {
    map<int, int> freq;
    for (auto num : nums) {
      freq[num]++;
    }
    int count = 0, n = nums.size();
    map<int, int> subarray_freq;
    int l = 0, r = 0;
    while (r < n) {
      subarray_freq[nums[r]]++;
      r++;
      while (l <= r && subarray_freq.size() > freq.size()) {
        subarray_freq[nums[l]]--;
        if (subarray_freq[nums[l]] == 0) {
          subarray_freq.erase(nums[l]);
        }
        l++;
        if (subarray_freq.size() == freq.size()) {
          count++;
        }
      }
      if (subarray_freq.size() == freq.size()) {
        count++;
      }
    }
    return count;
  }
};
int main() {
  vector<int> arr = {1, 3, 1, 2, 3};
  cout << Solution().countCompleteSubarrays(arr) << endl;
}
