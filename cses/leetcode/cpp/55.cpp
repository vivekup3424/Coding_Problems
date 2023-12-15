
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1 or n == 0)
            return true;
        int max = 0, start = 0;
        while (true)
        {
            for (int i = start; i <= nums[start]; i++)
            {
                int res = nums[i + start] + start;
                if (res > n)
                    return true;
                max = max > res ? max : res;
                start = max;
            }
        }
        return false;
    }
};

int main()
{
}