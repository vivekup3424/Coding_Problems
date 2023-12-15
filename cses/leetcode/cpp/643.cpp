/*
643. Maximum Average Subarray I
You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k that has the maximum
average value and return this value. Any answer with a calculation error
less than 10-5 will be accepted.
*/

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    double findMaxAverage(vector<int> &nums, int k)
    {
        int sum_so_far = 0;
        for (int i = 0; i < k; i++)
        {
            sum_so_far += nums[i];
        }
        int current_sum = sum_so_far;
        for (int i = k; i < nums.size(); i++)
        {
            current_sum = current_sum + nums[i] - nums[i - k];
            sum_so_far = max(current_sum, sum_so_far);
        }
        return (double)sum_so_far / (double)k;
    }
};
int main()
{
    vector<int> nums = {1, 12, -5, -6, 50, 3};
    int k = 4;
    Solution *A = new Solution();
    cout << A->findMaxAverage(nums, k) << endl;
}