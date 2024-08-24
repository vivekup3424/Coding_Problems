#include <bits/stdc++.h>
using namespace std;
int recurse(int idx, int N, int W, vector<int> &wt, vector<int> &val)
{
    if (idx == 0)
    {
        if (wt[idx] <= W)
        {
            return max(val[idx], 0);
        }
        else
        {
            return 0;
        }
    }
    else
    { // idx > 0
        if (wt[idx] <= W)
        {
            return max(recurse(idx - 1, N, W - wt[idx], wt, val) + val[idx],
                       recurse(idx - 1, N, W, wt, val));
        }
        else
        {
            // wt[idx] > W
            return recurse(idx - 1, N, W, wt, val);
        }
    }
}
int knapSack(int W, vector<int> &wt, vector<int> &val)
{
    int N = val.size();
    recurse(N - 1, N, W, wt, val);
}
int knapSack(int W, vector<int> &wt, vector<int> &val)
{
    int N = wt.size();
    int dp[N + 1][W + 1];
    // dp[i][j] = max value I can get by including till i balls
    // provided their total weight is j
    int maxi = 0;
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else
            {
                int first = INT_MIN, second = INT_MIN;
                if (wt[i - 1] <= j)
                {
                    // I can include the i-1 ball in knapsack
                    first = dp[i - 1][j - wt[i - 1]] + val[i - 1];
                }
                second = dp[i - 1][j];
                dp[i][j] = max(first, second);
                maxi = max(maxi, dp[i][j]);
            }
        }
    }
    return maxi;
}