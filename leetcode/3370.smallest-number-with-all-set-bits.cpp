/*
 * @lc app=leetcode id=3370 lang=cpp
 *
 * [3370] Smallest Number With All Set Bits
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int smallestNumber(int n) {
        return (1 << (int)(log(n)) - 1;
    }
};
// @lc code=end

