#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maximumGap(vector<int> &nums)
    {
        if (nums.size() < 2)
            return 0;
        int mini = *min_element(nums.begin(), nums.end());
        int maxi = *max_element(nums.begin(), nums.end());
        int range = maxi - mini + 1;
        vector<long long> freq(range, 0);
        for (int num : nums)
        {
            freq[num - mini] = 1;
        }
        // finding the max_difference
        int prev = 0;
        int max_width = 0;
        for (int i = 0; i < freq.size(); i++)
        {
            if (freq[i] != 0)
            {
                int current = i;
                max_width = max(max_width, current - prev);
                prev = current;
            }
        }
        return max_width;
    }
};