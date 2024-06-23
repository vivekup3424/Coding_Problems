#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    const int MOD = 1e9 + 7;

    int numberOfPermutations(int n, vector<vector<int>> &requirements)
    {
        int maxInversions = n * (n - 1) / 2;
        vector<vector<int>> dp(n + 1, vector<int>(maxInversions + 1, 0));

        dp[0][0] = 1;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= maxInversions; ++j)
            {
                for (int k = 0; k < i; ++k)
                {
                    if (j >= k)
                    {
                        dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % MOD;
                    }
                }
            }
        }

        // Filter permutations based on requirements
        int result = 0;
        for (int j = 0; j <= maxInversions; ++j)
        {
            bool valid = true;
            for (auto &req : requirements)
            {
                int endi = req[0] + 1; // Convert 0-based to 1-based index
                int cnti = req[1];
                if (dp[endi][cnti] == 0)
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                result = (result + dp[n][j]) % MOD;
            }
        }

        return result;
    }
};

int main()
{
    Solution solution;
    int n = 3;
    vector<vector<int>> requirements = {{2, 2}, {0, 0}};
    cout << solution.numberOfPermutations(n, requirements) << endl; // Output: 2
    return 0;
}
