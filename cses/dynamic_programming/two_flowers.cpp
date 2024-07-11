/**
 * There are N flowers. Each flower can either be a red flower or a white
 * flower. How many ways are there to arrange them in a line of length N such
 * that there are never more than M flowers of the same color in a row? 1 ≤ N, M
 * ≤ 5000
 *
 * DP[i][(0, 1)] = number of configurations if
 * i : first i flowers placed
 * (0, 1) : type of the ith flower
 */

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    int dp[n][2] = {0};

    // dp[i][x] = number of valid configurations if the last ith flower is of type
    // x

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i == 0)
            {
                dp[i][j] = 1;
            }
            else
            {
                /**
                 * If the ith flower is of type 0, we can place it and then place 1 . .
                 * . M flowers of type 1 in positions i+1 . . . i+M. This maintains the
                 * constraint of not having more than M contiguous flowers of the same
                 * type. We update the next M positions of the opposite flower.
                 */
                for (int k = 1; k <= m; k++)
                {
                    if (i + k < n)
                    {
                        dp[i + k][1] += dp[i][0];
                    }
                }
            }
        }
    }
    // Time Complexity = O(n*m)
    //  The answer is the sum of valid configurations for both types of flowers at
    //  position n-1
    cout << dp[n - 1][0] + dp[n - 1][1];
    return 0;
}