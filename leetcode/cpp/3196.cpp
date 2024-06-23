#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    long long maximumTotalCost(vector<int> &nums)
    {
        int n = nums.size();
        ll dp[n][2];
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                dp[0][0] = nums[0];
                dp[0][1] = nums[0];
            }
            else if (nums[i] >= 0)
            {
                dp[i][0] = dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + nums[i];
            }
            else if (nums[i] < 0)
            {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + nums[i];
                dp[i][1] = dp[i - 1][0] - nums[i];
            }
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};
int main()
{
    vector<int> nums = {-3, 0};
    cout << Solution().maximumTotalCost(nums);
}