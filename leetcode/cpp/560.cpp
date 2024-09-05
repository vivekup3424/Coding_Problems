#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> pref(n);
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                pref[i] = nums[i];
            }
            else
            {
                pref[i] = pref[i - 1] + nums[i];
            }
        }
    }
};