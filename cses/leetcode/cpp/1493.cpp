
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int longestSubarray(vector<int> &nums)
    {
        int n = nums.size();
        // find the length of largest substring containing
        // atmost one 0
        int start = 0, maxLen = 0, zeroCount = 0;
        for (int i = 0; i < n; i++)
        {
            zeroCount += (nums[i] == 0);
            while (zeroCount > 1)
            {
                zeroCount -= (nums[start] == 0);
                start++;
            }
            maxLen = max(maxLen, i - start);
        }
        return maxLen;
    }
};
int main()
{
}