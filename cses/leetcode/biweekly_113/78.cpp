#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
class Solution
{
    // I have made this solutiotn using bit manipulation
public:
    vector<vector<int>> subsets(vector<int> &nums) // 1,2,3
    {
        int n = nums.size();
        llu total = pow(2, n);
        vector<vector<int>> ans;
        for (llu i = 0; i < total; i++)
        {
            vector<int> currentSet;
            for (llu j = 0; j < n; j++)
            {
                if (i & (1 << j))
                {
                    currentSet.push_back(nums[j]);
                }
            }
            ans.push_back(currentSet);
        }
        return ans;
    }
};

class BackTracking
{
public:
    void backTrack(vector<int> &nums, vector<int> &current, vector<vector<int>> &ans, int idx)
    {
        if (idx == nums.size())
        {
            ans.push_back(current);
            return;
        }
        current.push_back(nums[idx]);
        backTrack(nums, current, ans, idx + 1);
        current.pop_back();
        backTrack(nums, current, ans, idx + 1);
    }
    vector<vector<int>> subsets(vector<int> nums)
    {
        vector<int> current;
        vector<vector<int>> ans;
        int idx = 0;
        backTrack(nums, current, ans, idx);
        return ans;
    }
};
int main()
{
    vector<int> nums = {1, 2};
    BackTracking A;
    vector<vector<int>> result = A.subsets(nums);
}