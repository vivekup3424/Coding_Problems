#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
int main()
{
    int t;
    cin >> t;
    vector<int> v(t);
    for (int i = 0; i < t; i++)
    {
        cin >> v[i];
    }
    int maxi = *max_element(v.begin(), v.end());
    vector<vector<ll>> dp(maxi + 1, vector<ll>(3, 0));
    for (int i = 1; i <= maxi; i++)
    {
        if (i == 1)
        {
            dp[1][1] = 1;
            dp[1][2] = 1;
        }
        else
        {
            dp[i][1] = (4 * dp[i - 1][1] + 1 * dp[i - 1][2]) % MOD;
            dp[i][2] = (1 * dp[i - 1][1] + 2 * dp[i - 1][2]) % MOD;
        }
    }
    for (auto i : v)
    {
        cout << (dp[i][1] + dp[i][2]) % MOD << endl;
    }
}