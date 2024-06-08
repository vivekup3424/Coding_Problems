#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int minimumDifference(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> dp(n + 1, 0);
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                dp[i] = nums[i];
            }
            else
            {
                int choice1 = abs(dp[i - 1] & nums[i] - k);
                int choice2 = abs(dp[i - 1] - k);
                dp[i] = min(choice1, choice2);
            }
        }
        return dp[n];
    }
};