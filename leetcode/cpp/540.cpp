// 540. Single Element in a sorted array

#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    int singleNonDuplicate(vector<int> &nums)
    {
        int result = 0, n = nums.size();
        for (const int &num : nums)
        {
            result ^= num;
        }
    }
    // Time COmplexity = O(n)
};
class Solution
{
public:
    bool isSafe(int n, int x)
    {
        if (0 <= x and x < n)
            return true;
        return false;
    }
    int singleNonDuplicate(vector<int> &nums)
    {
        int n = nums.size();
        int low = 0, high = n - 1;
        int r = binarySearch(nums, low, high, n);
        return r;
    }
    int binarySearch(vector<int> &nums, int low, int high, int n)
    {
        int mid = low + (high - low) / 2;
        if (isSafe(n, mid - 1))
        {
            if (nums[mid] != nums[mid - 1] and !isSafe(n, mid + 1))
            {
                return nums[mid];
            }
        }
        else if (isSafe(n, mid + 1))
        {
            if (!isSafe(n, mid - 1) and nums[mid] != nums[mid + 1])
            {
                return nums[mid];
            }
        }
        else if (isSafe(n, mid - 1) and isSafe(n, mid + 1))
        {
            if (nums[mid] != nums[mid - 1] and nums[mid] != nums[mid + 1])
            {
                return nums[mid];
            }
        }
        if (isSafe(n, mid - 1))
        {
            if ((nums[mid] != nums[mid - 1] and !((mid - 1) & 1)) or (nums[mid] == nums[mid - 1] and ((mid - 1) & 1)))
            {
                // alone is on left
                binarySearch(nums, low, mid - 1, n);
            }
        }
        binarySearch(nums, mid + 1, high, n);
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    int result = solution.singleNonDuplicate(nums);
    std::cout << "Single non-duplicate element: " << result << std::endl;
    return 0;
}
