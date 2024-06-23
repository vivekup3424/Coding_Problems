#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long countBadPairs(vector<int> &nums)
    {
        long long count = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            // i<j
            for (int j = i + 1; j < n; j++)
            {
                if (j - 1 != nums[j] - nums[i])
                {
                    count++;
                }
            }
        }
        return count;
    }
};