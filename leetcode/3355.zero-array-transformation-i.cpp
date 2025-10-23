/*
 * @lc app=leetcode id=3355 lang=cpp
 *
 * [3355] Zero Array Transformation I
 */
#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
       int n = nums.size();
       vector<int> freq(n+1,0) ;
       for(auto q : queries){
        auto l = q[0], r = q[1];
        freq[l] = 1;
        freq[r+1] = -1;
       }
    }
};
// @lc code=end

