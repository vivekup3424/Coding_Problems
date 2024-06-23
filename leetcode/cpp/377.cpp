
#include <bits/stdc++.h>
using namespace std;
// this problem is similar to unbounded knapsack problem

// using recursion
int coinChange(vector<int> &nums, int n, int target)
{
    if (target == 0)
    {
        return 1; // since the target value is empty , there is null ways to reach that sum, there is 1 way that is null
    }
    // n = nums.size() is the current index+1 of the elemen where we are looking
    else if (n == 0)
    {
        return 0; // since the array is empty hence there is no way to get the required sum
    }
    else if (nums[n - 1] <= target)
        // sum of not choosing that coin + sum of choosing that coinf multiple number of time
        return (coinChange(nums, n - 1, target) + coinChange(nums, n, target - nums[n - 1]));
    else
    {
        return coinChange(nums, n - 1, target);
    }
}
class Solution
{
public:
    int combinationSum4(vector<int> &nums, int target)
    {
        int n = nums.size();
        int dp[n + 1][target + 1];
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < target + 1; j++)
            {
                if (j == 0)
                    dp[i][j] = 1;
                else if (i == 0)
                    dp[i][j] = 0;
                else if (nums[i - 1] <= j)
                {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - nums[i - 1]];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][target];
    }
};
int main()
{
    vector<int> nums = {1, 2, 3};
    int target = 5;
    Solution A;
    cout << A.combinationSum4(nums, target);
    return 0;
}