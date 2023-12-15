
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxSubarrays(vector<int> &nums)
    {
        int totalAnd = nums[0];
        for (int i : nums)
        {
            totalAnd &= i;
        }
        if (totalAnd) // if total has an non-zero vue
            return 1;
        int currentAnd = -1;
        int ans = 0;
        for (int i : nums)
        {
            if (currentAnd == -1)
            {
                currentAnd = i;
            }
            else
            {
                currentAnd &= i;
            }
            if (currentAnd == totalAnd)
            {
                ans++;
                currentAnd = -1;
            }
        }
        return ans;
    }
};
int main()
{
    vector<int> v = {1, 0, 2, 1};
    Solution A = Solution();
    int n = A.maxSubarrays(v);
}