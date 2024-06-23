
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minPairSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int max = 0;
        for (int i = 0; i < nums.size() / 2; i++)
        {
            if (nums[i] + nums[nums.size() - 1 - i] > max)
                max = nums[i] + nums[nums.size() - 1 - i];
        }
        return max;
    }
};
int main()
{
}