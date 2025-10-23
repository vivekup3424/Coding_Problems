/*
 * @lc app=leetcode id=3356 lang=cpp
 *
 * [3356] Zero Array Transformation II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    bool isItPossible(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size();
        vector<int> freq(n + 1, 0);
        for (auto query : queries)
        {
            auto l = query[0], r = query[1], val = query[2];
            freq[l] = val;
            freq[r + 1] = -val;
        }
        for(int i = 1; i < n; i++){
            freq[i]+=freq[i-1];
        }
        for(int i = 0; i < n; i++){
            if(nums[i]>freq[i]) return false;
        }
        return true;
    }

public:
    int minZeroArray(vector<int> &nums, vector<vector<int>> &queries)
    {
    }
};
// @lc code=end
