#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int recurse(vector<int> a, int n, int m, int i)
{
    if (i == 0)
    {
        if (a[i] == 0)
        {
            return m;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (a[i] == 0)
        {
            int count = 0;
            int v = a[i - 1];
            if (v - 1 > 0)
            {
                a[i] = v - 1;
                count += recurse(a, n, m, i - 1);
            }
            if (v + 1 <= m)
            {
                a[i] = v + 1;
                count += recurse(a, n, m, i - 1);
            }
            a[i] = v;
            count += recurse(a, n, m, i - 1);
            return count;
        }
        else
        {
            return recurse(a, n, m, i - 1);
        }
    }
}
int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dp(n, vector<int>(m + 1, 0));
    int x0;
    cin >> x0;
    if (x0 == 0)
    {
        fill(dp[0].begin(), dp[0].end(), 1);
    }
    else
    {
        dp[0][x0] = 1;
    }
    for (int i = 1; i < n; i++)
    {
        int x;
        cin >> x;
        if (x == 0)
        {
            for (int j = 1; j <= m; j++)
            {
                for (int k : {j - 1, j, j + 1})
                {
                    if (k >= 1 && k <= m)
                    {
                        (dp[i][j] += dp[i - 1][j]) % MOD;
                    }
                }
            }
        }
        else
        {
            for (int)
        }
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    return 0;
}
