#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        //similar to matrix chain multiplication
        int n = stones.size();
        vector<vector<int>> dp(n,vector<int>(n,INT_MAX));
        for(int i = 0; i < n; i++){
            dp[i][i] = stones[i];
        }
        for(int i =0; i < n-1; i++){
            for(int j = 1; j < n; j++){
                for(int k = i; k < j; k++){
                    dp[i][i+j] = min(dp[i][i+j], abs(dp[i][k]-dp[k+1][j]));
                }
            }
        }
        return
    }
};
