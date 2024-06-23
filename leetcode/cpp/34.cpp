
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int binSearch(vector<int> nums, int target, bool findLowerBound)
    {
        int left = 0, right = nums.size() - 1;
        int index = -1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (target > nums[mid])
            {
                left = mid + 1;
            }
            else if (target < nums[mid])
            {
                right = mid - 1;
            }
            else
            {
                if (findLowerBound)
                {
                    index = mid;
                    right = mid - 1;
                }
                else
                {
                    index = mid;
                    left = mid + 1;
                }
            }
        }
        return index;
    }
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int lower = binSearch(nums, target, true);
        int upper = binSearch(nums, target, false);
        return {lower, upper};
    }
};
int main()
{
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    int target = 8;
    Solution A = Solution();
    A.searchRange(nums, target);
}