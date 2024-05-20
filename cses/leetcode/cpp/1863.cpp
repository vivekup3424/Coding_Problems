#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int subsetXORSum(vector<int> &nums)
    {
        // using bitmasking, yeah I could have solved this using
        // backtracking, but I wanted to try something new
        int n = nums.size();
        int total = (int)pow(2, n); // total number of subsets
        int sum = 0;
        for (int i = 0; i < total; i++)
        {
            int x = 0;
            for (int j = 0; j < n; j++)
            {
                if (i & (1 << j))
                {
                    x ^= nums[j];
                }
            }
            sum += x;
        }
        return sum;
    }
};