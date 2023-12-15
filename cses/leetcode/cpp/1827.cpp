
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minOperations(vector<int> &nums)
    {
        int sum = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] <= nums[i - 1])
            {
                int diff = nums[i - 1] - nums[i] + 1;
                nums[i] += diff;
                sum += diff;
            }
        }
        return sum;
    }
};
int main()
{
}