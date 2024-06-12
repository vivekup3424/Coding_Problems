#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int maxTotalReward(vector<int> &r)
    {
        sort(r.begin(), r.end());
        int n = r.size();

        // Find an upper bound for sum (this can be set as the sum of all elements in r)
        int sum_limit = accumulate(r.begin(), r.end(), 0);

        // Initialize the DP table
        vector<int> dp(sum_limit + 1, 0);
        int maxSum = 0;

        // Bottom-up DP approach with space optimization
        for (int idx = 0; idx < n; ++idx)
        {
            // Traverse from the end to the beginning to avoid overwriting values in the same iteration
            for (int sum = sum_limit; sum >= r[idx]; --sum)
            {
                dp[sum] = max(dp[sum], dp[sum - r[idx]] + r[idx]);
                maxSum = max(maxSum, dp[sum]);
            }
        }

        return maxSum;
    }
};

int main()
{
    Solution sol;
    vector<int> rewards = {1, 6, 4, 3, 2};
    cout << sol.maxTotalReward(rewards) << endl;
    return 0;
}
