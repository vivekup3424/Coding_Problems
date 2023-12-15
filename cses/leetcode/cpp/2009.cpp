// this was a hard question, consult editorial for the answer
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int upperBound(vector<int> &nums, int elment)
    {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int temp = nums[mid];
            if (elment == temp)
            {
                return mid + 1;
            }
            else if (elment < temp)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    }
    int minOperations(vector<int> &nums)
    {
        int n = nums.size();
        int min_op = INT_MAX;
        set<int> s(nums.begin(), nums.end());
        vector<int> v;
        for (int n : s)
        {
            v.push_back(n);
        }
        for (int i = 0; i < v.size(); i++)
        {
            int left = v[i];
            int right = left + n - 1;
            int upper_bound_index = upperBound(v, right);
            int count = n - (upper_bound_index - i);
            min_op = min(min_op, count);
        }
        return min_op;
    }
};
int main()
{
    vector<int> nums = {4, 2, 5, 3};
    Solution A = Solution();
    A.minOperations(nums);
    return 0;
}