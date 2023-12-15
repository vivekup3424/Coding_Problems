// use a temp data member to hold next greater element value and then traverse

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> findNextGreater(vector<int> &nums)
    {
        int n = nums.size();
        int m = -1;
        vector<int> results(n, -1);
        for (int i = n - 1; i >= 0; i--)
        {
            if (m > nums[i])
            {
                results[i] = m;
            }
            if (i != 0 and nums[i] > nums[i - 1])
            {
                m = nums[i];
            }
        }
        return results;
    }
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> results = findNextGreater(nums2);
        unordered_map<int, int> Indices;
        for (int i = 0; i < nums2.size(); i++)
        {
            Indices[nums2[i]] = i;
        }
        vector<int> elements;
        for (int num : nums1)
        {
            elements.push_back(results[Indices[num]]);
        }
        return elements;
    }
};
int main()
{
    vector<int> nums = {1, 2, 3, 4};
    Solution A = Solution();
    vector<int> resuls = A.findNextGreater(nums);
    return 0;
}