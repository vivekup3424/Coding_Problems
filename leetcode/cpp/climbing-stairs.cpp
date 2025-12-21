#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    int recurse(int n){
        if(n<=0)return n == 0;
        return recurse(n-1)+recurse(n-2);
    }
    int recurseWithMemo(int n, vector<int>& memo){
        if(n<=0) return n == 0;
        if(memo[n] != -1) return memo[n];
        return memo[n] = recurseWithMemo(n-1, memo) + recurseWithMemo(n-2, memo);
    }
    //bottom up dynamic programming approach
    int bottomUp(int n){
        vector<int> dp(n+1, 0);
        dp[0] = 1; dp[1] = 1;
        for(int i = 2; i <= n; i++){
            dp[i] = dp[i-1] + dp[i-2];
        }
    }
    int climbStairs(int n){
        vector<int> memo(n+1, -1);
        return recurseWithMemo(n, memo);
    }
};