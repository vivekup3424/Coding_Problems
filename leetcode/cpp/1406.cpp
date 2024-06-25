#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    string stoneGameIII(vector<int> &stoneValue)
    {
        int n = stoneValue.size();
        // 0 = Alice, 1 = Bob
        int dp[n + 1][2];
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j <= 1; j++)
            {
                if (j == 0)
                {
                    int choice1 = stoneValue[i] + dp[i - 1][1 - j];
                    int choice2 = stoneValue[i] + stoneValue[i - 1] + dp[i - 2][1 - j];
                    int choice3 = stoneValue[i] + stoneValue[i - 1] + stoneValue[i - 2] + dp[i - 3][j - 1];
                    dp[i][j] = max({choice1, choice2, choice3});
                }
                else
                {
                    // Bob's turn
                    int choice1 = -stoneValue[i] + dp[i - 1][1 - j];
                    int choice2 = -stoneValue[i] - stoneValue[i - 1] + dp[i - 2][1 - j];
                    int choice3 = -stoneValue[i] - stoneValue[i - 1] - stoneValue[i - 2] + dp[i - 3][j - 1];
                    dp[i][j] = max({choice1, choice2, choice3});
                }
            }
        }
    }
};