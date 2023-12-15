
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool isMonotonic(vector<int> &nums)
    {
        int n = nums.size();
        bool inc = false, dec = false;
        if (n <= 2)
            return true;
        for (int i = 0; i < n - 1; i++)
        {
            if (nums[i] < nums[i + 1])
            {
                inc = true;
            }
            else if (nums[i] > nums[i + 1])
            {
                dec = true;
            }
        }
        return inc ^ dec;
    }
};
int main()
{
    vector<int> nums = {6, 5, 4, 4};
    Solution A;
    A.isMonotonic(nums);
}