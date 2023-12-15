
#include <bits/stdc++.h>
using namespace std;
// solve this question using dp
class Solution
{
public:
    vector<int> countBits(int n)
    {
        vector<int> dp(n + 1, 0);
        dp[0] = 0;
        for (int i = 1; i < n + 1; i++)
        {
            dp[i] = dp[i / 2] + (i & 1);
        }
        return dp;
    }
    // Time complexity = O(n)
    // Space Complexity = O(1)
};
int main()
{
}