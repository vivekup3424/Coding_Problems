// 198. House Robber

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        int dp[n + 1];
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            if (i == 1)
            {
                dp[i] = nums[0];
            }
            else if (i == 2)
            {
                dp[i] = max(nums[0], nums[1]);
            }
            else
            {
                dp[i] = max(dp[i - 2], dp[i - 3]) + nums[i - 1];
            }
        }
        return max(dp[n - 1], dp[n]);
    }
};
// Using recursion
int rob(vector<int> &nums, int n)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    else if (n == 1)
        return nums[1];
    else if (n == 2)
        return max(nums[1], nums[0]);
    else
        return max(rob(nums, n - 2), rob(nums, n - 3)) + nums[n - 1];
}
int main()
{
}