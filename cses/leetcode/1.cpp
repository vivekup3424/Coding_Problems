
#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<int> ans;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            int x = target - nums[i];
            for (int j = i + 1; j < n; j++)
            {
                if (nums[j] == x)
                {
                    ans.push_back(i);
                    ans.push_back(j);
                    return ans;
                }
            }
        }
        return ans;
    }
    // Time-complexity = O(n^2)
    // Space-complexity = O(1)
};
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> hashMap;
        for (int i = 0; i < nums.size(); i++)
        {
            int comp = target - nums[i];
            if (hashMap.find(comp) != hashMap.end())
            {
                return {hashMap[comp], i};
            }
            hashMap[nums[i]] = i;
        }
        return {};
    }
    // Time-complexity = O(n)
    // Space-complexity = O(n)
};
int main()
{
}