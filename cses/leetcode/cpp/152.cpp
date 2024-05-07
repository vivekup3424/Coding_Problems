
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxProduct1(vector<int> &nums)
    {
        // Brute force approach
        int max_product = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int current_product = 1;
            for (int j = i; j < nums.size(); j++)
            {
                current_product *= nums[j];
                max_product = max(current_product, max_product);
            }
        }
        return max_product;
    }
    int max_sum_subarray(vector<int> &nums)
    {
        int max_sum = 0, current_sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            current_sum += nums[i];
            if (current_sum < 0)
            {
                current_sum = 0;
            }
        }
    }
    int maxProduct(vector<int> &nums)
    {
        int n = nums.size();
        vector<pair<int, int>> dp(n, {0, 0});
        int max_product = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            max_product = max(max_product, nums[i]);
        }

        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                dp[i].first = nums[0];
                dp[i].second = 0;
            }
            else
            {
                dp[i].first = max(dp[i - 1].first, dp[i - 1].second) * nums[i];
                dp[i].second = min(dp[i - 1].first, dp[i - 1].second);
            }
            max_product = max({dp[i].first, dp[i].second, max_product});
        }
        return max_product;
    }
};
int main()
{
    vector<int> v = {2, -5, -2, -4, 3};
    Solution A;
    A.maxProduct(v);
}