#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<char>> grid(H, vector<char>(W));
    vector<vector<int>> dp(H, vector<int>(W, 0));

    // Input the grid
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            cin >> grid[i][j];
        }
    }

    // Initialize the starting point
    dp[0][0] = 1;

    // Fill the DP table
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (grid[i][j] == '#')
            {
                dp[i][j] = 0; // Wall cell, no paths through it
            }
            else
            {
                if (i > 0)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
                }
                if (j > 0)
                {
                    dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
                }
            }
        }
    }

    // Output the result
    cout << dp[H - 1][W - 1] << endl;
    return 0;
}
