#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int largestNumber(vector<int> &cost, int target)
    {
        int n = cost.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= target; j++)
            {
                if (j == 0)
                {
                    dp[i][j] = 1;
                }
                else if (i == 0)
                {
                    if (j == cost[i])
                    {
                        dp[i][j] = 1;
                    }
                    else
                    {
                        dp[i][j] = 0;
                    }
                }
                if (j <= cost[i])
                {
                    dp[i][j] = max(dp[i][j - cost[i]], dp[i - 1][j]);
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n - 1][target];
    }
};
int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    int target;
    cin >> target;
    cout << Solution().largestNumber(v, target) << endl;
}