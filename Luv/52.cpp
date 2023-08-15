// How to GENERATE SUBSETS using Bit-Masking | CP Course | EP 52

#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> subsets(vector<int> &nums)
{
    int n = nums.size();
    int subset_count = (1 << n);
    vector<vector<int>> subsets;
    for (auto mask = 0; mask < subset_count; mask++)
    {
        vector<int> subset;
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i) != 0)
            {
                subset.push_back(nums[i]);
            }
            subsets.push_back(subset);
        }
    }
    return subsets;
}
// Time complexity = O(n*2^n)
int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    vector<vector<int>> subsets;
}