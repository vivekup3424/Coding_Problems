#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    long long maximumOr(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<long long> pref(n, 0);
        vector<long long> suff(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                pref[i] = 0;
            }
            else
            {
                pref[i] = pref[i - 1] | nums[i - 1];
            }
        }
        for (int i = n - 1; i >= 0; i--)
        {
            if (i == n - 1)
            {
                suff[i] = 0;
            }
            else
            {
                suff[i] = suff[i + 1] | nums[i + 1];
            }
        }
        long long maxAns = 0;
        for (int i = 0; i < n; i++)
        {
            maxAns = max(maxAns, pref[i] | suff[i] | (nums[i] * (long long)1 << k));
        }
        return maxAns;
    }
};