
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minAbsoluteDifference(vector<int> &nums, int x)
    {
        int minDiff = INT_MAX, start = 0, i = x, n = nums.size();
        for (; start + x < n and (start < n / 2); start++)
        {
            for (; i < n; i++)
            {
                int diff = abs(nums[start] - nums[i]);
                minDiff = min(diff, minDiff);
            }
        }
        return minDiff;
    }
};
int main()
{
}