
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
  int maxSubArray(vector<int> &nums)
  {
    int ans = INT_MIN;
    int sum = 0;

    for (const int num : nums)
    {
      sum = max(num, sum + num);
      ans = max(ans, sum);
    }

    return ans;
  }
};

class Solution1
{
  // naive approach
  int maxSubArray(vector<int> &nums)
  {
    int max_so_far = INT_MIN;
    for (int i = 0; i < nums.size(); i++)
    {
      int current_sum = 0;
      for (int j = i; j < nums.size(); j++)
      {
        current_sum += nums[j];
        max_so_far = max(current_sum, max_so_far);
      }
    }
    return max_so_far;
  }
};
int main()
{
}