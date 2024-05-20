#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<bool> isArraySpecial(vector<int> &nums, vector<vector<int>> &queries)
    {
        // using prefix sum calculations
        int n = nums.size();
        if (n < 2)
        {
            vector<bool> v(queries.size(), true);
            return v;
        }
        vector<int> parity_prefix;
        for (int i = 1; i < n; i++)
        {
            int value = (nums[i] % 2 != nums[i - 1] % 2);
            parity_prefix.push_back(value);
        }
        // prefix-sum
        for (int i = 1; i < parity_prefix.size(); i++)
        {
            parity_prefix[i] += parity_prefix[i - 1];
        }

    }
};