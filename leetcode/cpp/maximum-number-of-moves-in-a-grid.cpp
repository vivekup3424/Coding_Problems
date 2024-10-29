#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<int>> dp(rows,vector<int>(cols,0));
        for(int i = 0; i < rows; i++){
            for(int j = cols-2; j >= 0; j--){
                int One = 0, Two = 0, Three = 0;
                if(i+1 < rows and grid[i][j]<grid[i+1][j+1]){
                    One = 1 + dp[i+1][j+1];
                }
                if(grid[i][j] < grid[i][j+1]){
                    Two = 1 + dp[i][j+1];
                }
                if(i-1 >= 0 and grid[i][j]<grid[i-1][j+1]){
                    Three = 1 + dp[i-1][j+1];
                }
                dp[i][j] = max({One,Two,Three});
            }
        }
        int maxi = 0;
        for(int i = 0; i < rows; i++){
            maxi = max(maxi,dp[i][0]);
        }
        return maxi;
    }
};
