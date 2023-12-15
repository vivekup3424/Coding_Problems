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
#define N 1005
#define mod 1000000007
int dp[N][N];
void printLongestCommonSubstring(string s1, string s2)
{
    int n = s1.size(), m = s2.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = 0;
        }
    }
}
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        string s1;
        string s2 = s1;
        s1.reserve();
        printLongestCommonSubstring(s1, s2);
        cin >>
            s1;
    }
}