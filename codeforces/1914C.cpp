#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        vector<int> b(n);
        for (int i = 0; i < n; i++)
        {
            cin >> b[i];
        }
        int dp[n + 1][k + 1];:
        for(int i = 0; i < n+1; i++)
        {
            for (int j = 0; j < k + 1; j++)
            {
                if (i == 0)
                {
                    dp[i][j] = 0;
                }
                else if (j == 0)
                {
                    dp[i][j] = 0;
                }
                else if (a[i - 1] <= j)
                {
                    dp[i][j] = max(b[i - 1] + dp[i - 1][j - a[i - 1]], dp[i - 1][j]);
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }

    return 0;
}
