#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //this problem is similar to coin change problem
    //in that we can generate all coin value that is
    //perfect squares
    //then find the minimum number of coin change needed to get
    //that much amount
    int numSquares(int amount) {
        vector<int> perfectSquares; //Coins
        for(int i = 1; i <=amount; i++){
            int square = i * i;
            if(square > amount){
                break;
            }else{
                perfectSquares.push_back(square);
            }
        }
        int n = perfectSquares.size();
        vector<int> dp(amount+1, INT_MAX);
        dp[0] = 0;
        for(int i = 1; i <= amount; i++){
            for(auto coin: perfectSquares){
                //also similar to LIS
                if(i-coin>=0){
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
