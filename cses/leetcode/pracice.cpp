#include <bits/stdc++.h>
using namespace std;
int frogJump(int n, vector<int> &heights)
{
    vector<int> dp(n, 0);
    for (int i = 0; i <= n; i++)
    {
        if (i == 1)
        {
            dp[i] = 0;
        }
        else if (i == 2)
        {
            dp[i] = abs(heights[1] - heights[0]);
        }
        else
        {
            dp[i] = min(abs(heights[i - 1] - heights[i - 2]) + dp[i - 1], abs(heights[i - 1] - heights[i - 3]) + dp[i - 2]);
        }
    }
    return dp[n];
}

int main()
{
    int n = 4;
    vector<int> heights = {10, 20, 30, 10};
    int m = frogJump(n, heights);
    cout << m << endl;
}