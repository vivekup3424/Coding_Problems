// 198. House Robber

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int rob1(vector<int> &nums)
    {
        // this code works
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
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                dp[i] = nums[0];
            }
            else if (i == 1)
            {
                dp[1] = max(nums[0], nums[1]);
            }
            else
            {
                int one = 0, two = 0;
                if (i - 2 >= 0)
                {
                    one = nums[i - 2];
                }
                if (i - 3 >= 0)
                {
                    two = nums[i - 3];
                }
                dp[i] = max(one, two) + nums[i];
            }
        }
        return max(dp[n - 1], dp[n - 2]);
    }
};
// Using recursion
int rob(vector<int> &nums, int n)
{
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
    vector<int> v = {2, 7, 9, 3, 1};
    Solution A;
    A.rob(v);
}