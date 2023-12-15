
#include <bits/stdc++.h>
using namespace std;
const int N = 59;
int dp[N];
class Solution
{
public:
    int integerBreak(int n)
    {
        fill(dp, dp + N, 1);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j < i; j++)
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
        }
        return dp[n];
    }
};
int main()
{
}