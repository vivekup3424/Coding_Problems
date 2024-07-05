#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int maximumLength(vector<int> &nums, int k)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            nums[i] = (nums[i]) % k;
        }
        vector<vector<int>> dp(k, vector<int>(n, 0));
        for (int i = 1; i < k; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (j == 0)
                {
                    dp[nums[j] % k][j] = 1;
                }
                else if (j == 1)
                {
                    dp[nums[j] % k][j] = 1;
                }
                else
                {
                    dp[nums[j] % k][j] = max(dp)
                }
            }
        }
    }
};