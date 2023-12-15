
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> rearrangeArray(vector<int> &nums)
    {
        int i = 0, j = 0;

        while (j < nums.size())
        {
            if (nums[j] * nums[0] > 0) // same sign as initial element=> skip this node
            {
                j++;
            }
            else
            {
                swap(nums[++i], nums[j++]);
            }
        }
        return nums;
    }
};
int main()
{
}