
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    long long maximumTripletValue(vector<int> &nums)
    {
        int n = nums.size();
        long long max_left[n], max_right[n];
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
                max_left[i] = nums[i];
            else
                max_left[i] = max(max_left[i - 1], (long long)nums[i]);
        }
        for (int i = n - 1; i >= 0; i--)
        {
            if (i == n - 1)
                max_right[i] = nums[i];
            else
                max_right[i] = max(max_right[i + 1], (long long)nums[i]);
        }
        long long result = 0;
        for (int i = 0; i < n; i++)
        {
            if (i != 0 && i != n - 1)
            {
                long long val = (max_left[i - 1] - nums[i]) * max_right[i + 1];
                result = max(result, val);
            }
        }
        return result;
    }
};
int main()
{
    vector<int> v = {12,
                     6,
                     1,
                     2,
                     7};
    Solution A = Solution();
    A.maximumTripletValue(v);
    return 0;
}