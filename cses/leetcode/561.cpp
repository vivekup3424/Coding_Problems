
#include <bits/stdc++.h>
using namespace std;
// Method 1: Using counting sort
class Solution
{
public:
    int arrayPairSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int ans = 0, n = nums.size();
        for (int i = n - 2; i > 0; i -= 2)
        {
            ans += nums[i];
        }
        return ans;
    }
};
int main()
{
}