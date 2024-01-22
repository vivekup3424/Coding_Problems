#include <bits/stdc++.h>
using namespace std;
const int INF  = 10001;
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
       int rows = matrix.size(), cols = matrix[0].size();
       vector<vector<int>> dp(rows,vector<int>(cols,INF));
        //dp[i][j] denotes the minimum sum to get to cell[i][j] from 0th rows
       //if we are at the starting position
       for(int j = 0;j < cols; j++){
        dp[0][j] = matrix[0][j];
       }

       for(int i = 1; i < rows;i++){
        for(int j = 0;j < cols;j++){
            //cost to fall from above
            int up = matrix[i][j] + dp[i-1][j];

            //leftdiagonal
            int leftdiagonal = matrix[i][j];
            if(j-1>=0){
                leftdiagonal += dp[i-1][j-1];
            }
            else
            {
                leftdiagonal = INF;
            }

            int rightdiagonal = matrix[i][j];
            if(j+1 < cols){
                rightdiagonal += dp[i-1][j+1];
            } else{
                rightdiagonal = INF;
            }
            dp[i][j] = min({up, leftdiagonal, rightdiagonal});
        }
       }

       int minima = INF;
       for(int j = 0; j < cols;j++){
        minima = min(minima, dp[rows-1][j]);
       }
       return minima;
    }
};