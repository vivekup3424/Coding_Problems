#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int subarraysDivByK(vector<int> &nums, int k)
    {
        int n = nums.size();
        map<int, int> mp;
        vector<int> pref(n);
        // construct the prefix sum
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
            int rem = pref[i] % k;
            mp[rem]++;
        }
        int count = 0;
        for (auto it : mp)
        {
            count += ((it.second) * (it.second - 1)) / 2;
            if (it.first == 0 and it.second == 1)
            {
                count = 1;
            }
        }
        return count;
    }
};