#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int sum = accumulate(rolls.begin(),rolls.end(),0);
        int total = mean * (rolls.size() + n) - sum;
        vector<int> ans(n,1);
        if(total < n || total > 6*n){
            return {};
        }
        total -= n; //assigning each one of them one, since at
        //least one is missing from each move
        for(int i = 0;i < n and total >0; i++){
            ans[i] += min(total,5);
            total -= min(total,5);
        }
        return ans;
    }
};