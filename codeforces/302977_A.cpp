#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
int main()
{
    fast_io();
    lli n;
    cin >> n;
    lli dp[n + 1];
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = 2 * dp[i - 2];
    }
    cout << dp[n] << endl;
}