
#include <bits/stdc++.h>
using namespace std;
// Method 1:- Using vectors
class Solution
{
public:
    vector<int> pivotArray(vector<int> &nums, int pivot)
    {
        vector<int> lessThan, equalTo, GreaterThan;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] < pivot)
            {
                lessThan.push_back(nums[i]);
            }
            else if (nums[i] == pivot)
            {
                equalTo.push_back(nums[i]);
            }
            else if (nums[i] > pivot)
            {
                GreaterThan.push_back(nums[i]);
            }
        }
        // Join the three vectors
        vector<int> result;
        result.insert(result.end(), lessThan.begin(), lessThan.end());
        result.insert(result.end(), equalTo.begin(), equalTo.end());
        result.insert(result.end(), GreaterThan.begin(), GreaterThan.end());

        return result;
    }
};
int main()
{
}