#include <bits/stdc++.h>
#include <utility>
using namespace std;

class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        //creating a monotonically increasing stack
        stack<pair<int,int>> stk;
        long long score = 0;
        int n  = nums.size();
        for (int i = 0; i < n; i++) {
            if(stk.size()==0 || nums[i] >stk.top().first){
                stk.push({nums[i],i});
            }
        }
        int last = n-1;
        while(stk.size()>0){
            auto p = stk.top();
            stk.pop();
            score += (long long)p.first*(long long)(last-p.second);
            last  = p.second;
        }
        return score;
    }
};
