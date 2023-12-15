
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minimumRightShifts(vector<int> nums)
    {
        int len = nums.size(); // 3,4,5,1,2
        int ans = 0, index = -1, count = 0;
        int i;
        for (i = 0; i < len - 1; i++)
        {
            if (nums[i] > nums[i + 1]) // 1,3,5
            {
                index = i + 1;
                count++;
            }
        }
        if (count == 1)
        {
            if (index != -1 && nums[len - 1] < nums[0])
                ans = len - index;
            if (index == -1 && i == len - 2)
                ans = 0;
            if (index != -1 && nums[len - 1] > nums[0])
                ans = -1; // 2,1,4
        }
        else
            ans = -1;

        return ans;
    }
} int main()
{
}