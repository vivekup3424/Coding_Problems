// target is either: A subarray of nums, or prefix_sum[i] +  k * sum(nums) + suffix_sum[j] for some i, j, k. , hence for these three value
#include <bits/stdc++.h>
using namespace std;
class Solution1
{
    // naive approach using sliding window
public:
    int minSizeSubarray(vector<int> &nums, int target)
    {
        int n = nums.size();
        vector<int> infiniteArray(2 * n);
        for (int i = 0; i < n; i++)
        {
            infiniteArray[i] = nums[i];
            infiniteArray[i + n] = nums[i];
        }
        int minLength = INT_MAX, currentLength = 0;
        int start = 0, end = 0;
        int currentSum = 0;
        while (end != 2 * n)
        {
            currentSum += infiniteArray[end];
            if (currentSum == target)
            {
                currentLength = end - start + 1;
                minLength = min(minLength, currentLength);
                currentSum = 0;
                start = end + 1;
                end++;
            }
            else if (currentSum < target)
            {
                end++;
            }
            else
            {
                currentSum = 0;
                start = end + 1;
                end++;
            }
        }
        return minLength == INT_MAX ? -1 : minLength;
    }
};
class Solution
{
public:
    int minSizeSubarray(vector<int> &nums, int target)
    {
        int nums_sum = 0;
        for (auto num : nums)
            nums_sum += num;
        if (nums_sum < target)
        {
                }
    }
};
int main()
{
    vector<int> nums = {1, 2, 3};
    int target = 5;
    Solution s;
    cout << s.minSizeSubarray(nums, target) << endl;
}