#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long sumDigitDifferences(vector<int> &nums)
    {
        int temp = nums.front();
        int N = 0;
        for (; temp > 0; temp /= 10)
        {
            N++;
        }
        int total = 0;
        int mod = 10;
        int n = nums.size();
        for (int i = 0; i < N; i++)
        {
            int sum = 0;
            unordered_map<int, int> mp;
            for (int i = 0; i < n; i++)
            {
                int x = nums[i] % mod;
                nums[i] /= mod;
                sum += 1;
                mp[x] += 1;
            }
            int current_total = 0;
            for (auto it : mp)
            {
                current_total += (it.second) * (sum - it.second);
            }
            total += ((current_total) / 2);
        }
        return total;
    }
};