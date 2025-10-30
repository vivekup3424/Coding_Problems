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
    bool isItPossible(vector<int> &nums, vector<vector<int>> &queries, int k)
    {
        int n = nums.size();
        vector<int> freq(n + 1, 0);
        for (int i = 0; i < k; i++)
        {
            vector<int> &query = queries[i];
            auto l = query[0], r = query[1], val = query[2];
            freq[l] += val;
            freq[r + 1] -= val;
        }
        for (int i = 1; i < n; i++)
        {
            freq[i] += freq[i - 1];
        }
        for (int i = 0; i < n; i++)
        {
            if (nums[i] > freq[i])
                return false;
        }
        return true;
    }

public:
    int minZeroArray(vector<int> &nums, vector<vector<int>> &queries)
    {
        int l = 0, r = queries.size();
        while(l < r){
            int mid = (l+r)/2;
            int isZeroPossible = isItPossible(nums,queries, mid);
            if(isZeroPossible){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        // Check if even with all queries it's possible
        if (l == queries.size() && !isItPossible(nums, queries, queries.size())) {
            return -1;
        }
        return l;
    }
};
// @lc code=end
