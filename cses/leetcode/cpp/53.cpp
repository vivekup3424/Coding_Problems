
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
  int maxSubArray(vector<int> &nums)
  {
    int max_so_far = 0, current_max = 0, start = 0;
    for (int i = 0; i < nums.size(); i++)
    {
    }
  }
} int main()
{
}