
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target, int ignoreIndex)
    {
        unordered_map<int, int> hashMap;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i == ignoreIndex)
            {
                continue;
            }
            int comp = target - nums[i];
            if (hashMap.find(comp) != hashMap.end())
            {
                return {hashMap[comp], i};
            }
            hashMap[nums[i]] = i;
        }
        return {};
    }
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        int n = nums.size();
        int a = 0, b = 0, c = 0;
        vector<vector<int>> results;
        for (int i = 0; i < n; i++)
        {
            vector<int> r;
            a = nums[i];
            r = twoSum(nums, -a, i);
            if (!r.empty())
            {
                results.push_back({a, r[0], r[i]});
            }
        }
        return results;
    }
};
int main()
{
}