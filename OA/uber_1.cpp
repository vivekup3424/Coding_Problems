#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    ll minTime(vector<pair<ll, ll>> tasks, ll n, ll T, ll k)
    {
        // k = min score required
        // task.first = time for task i
        // task.second = score for task i

        // going to do the dp part
        vector<vector<ll>> dp(n + 1, vector<ll>(T + 1, 0));
        unordered_map<ll, ll> mp;
        ll minTime = INT_MIN;
        ll maxScore = INT_MIN;
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= T; j++)
            {
                if (i == 0 || j == 0)
                {
                    dp[i][j] = 0;
                }
                else if (tasks[i - 1].first > T)
                {
                    dp[i][j] = dp[i - 1][j]; // I am skipping the ith item
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j - tasks[i - 1].first],
                                   dp[i - 1][j]);
                }
                if (mp.find(dp[i][j]) == mp.end())
                {
                    mp[dp[i][j]] = T - j;
                }
                else
                {
                    mp[dp[i][j]] = min(mp[dp[i][j]], T - j);
                }
                if (dp[i][j] > maxScore)
                {
                    maxScore = dp[i][j];
                    minTime = mp[maxScore];
                }
            }
        }
        if (maxScore < k)
        {
            return -1;
        }
        else
            return minTime;
    }
};