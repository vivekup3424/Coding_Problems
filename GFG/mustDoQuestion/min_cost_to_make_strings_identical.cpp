#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int findMinCost(string x, string y, int costX, int costY)
    {
        // get the dp-matrix
        int n = x.size();
        int m = y.size();
        int dp[n + 1][m + 1];
        memset(dp, 0, (n + 1) * (m + 1));
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < m + 1; j++)
            {
                if (i == 0 or j == 0)
                {
                    dp[i][j] = 0;
                }
                else if (x[i - 1] == y[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // get the LCS(print the string)
        int lengthLCS = dp[n][m];
        int i = n, j = m;
        char LCS[lengthLCS];
        for (; i > 0 and j > 0;)
        {
            if (x[i - 1] == y[j - 1])
            {
                LCS[dp[i][j] - 1] = x[i - 1];
                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1])
            {
                i--;
            }
            else
            {
                j--;
            }
        }
        for (int i = 0; i < lengthLCS; i++)
        {
            printf("%d", LCS[i]);
        }

        int sum = 0;
        sum += costX * (n - lengthLCS);
        sum += costY * (m - lengthLCS);
        cout << "Sum = " << sum << endl;
        return sum;
    }
};