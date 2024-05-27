#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int kPalindrome(string s, int n, int k)
    {
        string temp = s;
        reverse(temp.begin(), temp.end());
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                if (i == 0 or j == 0)
                {
                    dp[i][j] = 0;
                }
                else if (s[i - 1] == temp[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        if (n - dp[n][n] <= k)
            return 1;
        else
            return 0;
    }
};