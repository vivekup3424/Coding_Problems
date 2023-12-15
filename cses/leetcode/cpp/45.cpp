// 45. Jump Game II

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int jump(vector<int> &nums)
    {
        if (nums.size() == 1)
        {
            return 0;
        }
        int start = 0, max = 0, step = 0;
        while (true)
        {
            for (int i = 1; i <= nums[start]; i++)
            {
                int result = nums[start + i] + start;
                if (result > nums.size() - 1)
                {
                    return step + 1;
                }
                else if (result > max)
                {
                    max = result;
                }
            }
            start = max;
            step++;
        }
        return step;
    }
};
class Solution2
{
public:
    int jump(vector<int> &nums)
    {
        int n = nums.size(), steps = 0, maxReach = 0, currMaxReach = 0;
        for (int i = 0; i < n - 1; i++)
        {
            currMaxReach = max(currMaxReach, i + nums[i]);
            if (i == maxReach)
            {
                steps++;
                maxReach = currMaxReach;
            }
        }
        return steps;
    }
};
int main()
{
    vector nums = {2, 3, 0, 1, 4};
    Solution *A = new Solution();
    int ans = A->jump(nums);
    cout << ans << endl;
}
