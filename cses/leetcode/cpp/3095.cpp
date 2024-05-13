#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumSubarrayLength(vector<int> &nums, int k)
    {
        int minLegth = INT_MAX;
        for (int i = 0; i < nums.size(); i++)
        {
            int currentLength = 0, currentValue = 0;
            for (int j = i; j < nums.size(); j++)
            {
                currentValue |= nums[j];
                currentLength++;
                if (currentValue >= k)
                {
                    minLegth = min(minLegth, currentLength);
                    break;
                }
            }
        }
        return minLegth == INT_MAX ? -1 : minLegth;
    }
};