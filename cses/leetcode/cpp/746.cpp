// I am improving little by little

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        cost.push_back(0);
        int dp[n + 1];
        for (int i = 0; i <= n; i++)
        {
            if (i == 0)
                dp[i] = cost[i];
            else if (i == 1)
                dp[i] = cost[i];
            else
            {
                dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
            }
        }
        return dp[n];
    }
};
int main()
{
    vector<int> cost = {10, 15, 20};
    Solution A = Solution();
    int n = A.minCostClimbingStairs(cost);
}