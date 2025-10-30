/*
 * @lc app=leetcode id=3461 lang=cpp
 *
 * [3461] Check If Digits Are Equal in String After Operations I
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string sumDigits(string s){
        if(s.length() <= 2){
            return s;
        }
        string temp;
        for(int i = 1; i < s.length(); i++){
            int first = s[i-1] - '0';
            int second = s[i-1] - '0';
            int val = (first+second)%10;
            temp.push_back('0'+val);
        }
        return sumDigits(temp);
    }
    bool hasSameDigits(string s) {
        string answer = sumDigits(s);
        return answer.front() == answer.back();
    }
};
// @lc code=end

