
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int i = 0, j = nums.size() - 1;
        int sum;
        vector<int> ans;
        while (i < j)
        {
            sum = nums[i] + nums[j];
            if (sum == target)
            {
                ans.push_back(i);
                ans.push_back(j);
                return ans;
            }
            else if (sum > target)
            {
                j--;
            }
            else
            {
                i++;
            }
        }
        return ans;
    }
};
int main()
{
}