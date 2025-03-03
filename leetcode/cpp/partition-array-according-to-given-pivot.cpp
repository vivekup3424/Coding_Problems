#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> pivotArray(vector<int> &nums, int pivot)
    {
        // place all elements less than pivot to left
        int i = 0, j = 0, n = nums.size();
        while (j < n)
        {
            if (nums[j] < pivot)
            {
                swap(nums[i], nums[j]);
                i += 1;
            }
            j += 1;
        }
        // place all the elements greater than pivot to right
        i = n - 1, j = n - 1;
        while (j >= 0)
        {
            if (nums[j] > pivot)
            {
                swap(nums[i], nums[j]);
                i -= 1;
            }
            j -= 1;
        }
        return nums;
    }
};