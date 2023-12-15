
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    long long countSubarrays(vector<int> &nums, int k)
    {
        int n = nums.size();
        int maxElement = INT_MIN;
        for (int i : nums)
        {
            maxElement = max(maxElement, i);
        }
        // I need to only store the frequency of maxElement in a subarray
        // hence I dont need a freq map, but rather constant space
        int freq = 0; // freq of maxElement in current subarray
        long long counter = 0;
        int l = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == maxElement)
            {
                freq++;
            }
            while (freq >= k and l < n)
            {
                counter++;
                if (nums[l] == maxElement)
                {
                    freq--;
                    l++;
                }
            }
        }
        return counter;
    }
};
int main()
{
}