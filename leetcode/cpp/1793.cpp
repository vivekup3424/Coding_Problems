#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maximumScore(vector<int> &nums, int k)
    {
        int l = k, r = k, cur_min = nums[k], res = nums[k];
        int n = nums.size();
        while (l > 0 || r < n - 1)
        {
            int left = l > 0 ? nums[l - 1] : 0;
            int right = r < n - 1 ? nums[r + 1] : 0;
            if (left > right)
            {
                l--;
                cur_min = min(cur_min, left);
            }
            else
            {
                r++;
                cur_min = min(cur_min, right);
            }
            res = max(res, ((cur_min) * (r - l + 1)));
        }
        return res;
    }
};

int main()
{
    vector<int> nums = {1, 4, 3, 7, 4, 5};
    int k = 3;
    Solution A = Solution();
    A.maximumScore(nums, k);
    return 0;
}