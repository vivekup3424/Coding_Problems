// sort the array, take a pivot elment and then use 2-pointer approach => Time complexity = O(n^2)
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int threeSumSmaller(vector<int> &nums, int target)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; i++)
        {
            if (i > 0 and nums[i] == nums[i - 1])
            {
                i++;
                continue; // avoiding the duplicates
            }
            int a = nums[i];
            int start = i + 1, end = n - 1;
            while (start < end)
            {
                int b = nums[start];
                int c = nums[end];
                if (a + b + c >= target)
                {
                    c--;
                }
                else
                {
                    return a + b + c;
                }
            }
        }
    }
};
int main()
{
}