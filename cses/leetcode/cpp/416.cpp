
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int sum = 0;
        for (auto num : nums)
        {
            sum += num;
        }
        if (sum & 1)
            return false;
        int half = sum / 2;
        int n = nums.size();
        bool dp[n + 1][half + 1];
        for (int i = 0; i <= nums.size(); i++)
        {
            for (int j = 0; j <= half; j++)
            {
                if (i == 0)
                {
                    dp[i][j] = false;
                }
                else if (j == 0)
                {
                    dp[i][j] = true;
                }
                else if (nums[i] <= j)
                {
                    dp[i][j] = dp[i + 1][j] || dp[i + 1][j - nums[i - 1]];
                }
                else
                {
                    dp[i][j] = dp[i + 1][j];
                }
            }
        }
        return dp[n][half];
    }
};
int main()
{
}