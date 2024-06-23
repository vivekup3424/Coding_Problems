#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int minPatches(vector<int> &nums, int n)
    {
        sort(nums.begin(), nums.end());
        int count = 0;
        ll smallestNumber = 0;
        vector<int> missingValues;
        for (int i = 0; i < nums.size();)
        {
            if (smallestNumber >= nums[i] - 1)
            {
                smallestNumber += nums[i];
                i++;
            }
            else
            {
                count++; // inserting a number(smallestNumber+1)
                missingValues.push_back(smallestNumber + 1);
                smallestNumber += smallestNumber + 1;
            }
        }
        while (smallestNumber < n)
        {
            count++;
            smallestNumber += smallestNumber + 1;
        }
        return count;
    }
};
int main()
{
    int n = 20;
    vector<int> v = {1, 5, 10};
    Solution().minPatches(v, n);
}
