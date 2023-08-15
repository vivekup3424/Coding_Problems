// Your task is to count the number of ways to construct sum n by
// throwing a dice one or more times. Each throw produces an outcome between 1 and 6.

// https://codeforces.com/blog/entry/70018
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
const int M = 1e9 + 7;
// constraint n < 10^6
#define MAX 1000000
int dp[MAX];
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

// dp[n] = sum of ways to have a sum of 4
int main()
{
    fast_io();
    int T;
    cin >> T;
    dp[0] = 1;
    // dp[1] = 1;
    // dp[2] = 2;
    // dp[3] = 4;
    // dp[4] = 8;
    // dp[5] = 16;
    // dp[6] = 32;
    for (int i = 1; i <= T; i++)
    {
        for (int j = 1; j <= 6 && i - j >= 0; j++)
        {
            (dp[i] += dp[i - j]) %= M;
        }
    }
    cout << dp[T] << endl;
    return 0;
}