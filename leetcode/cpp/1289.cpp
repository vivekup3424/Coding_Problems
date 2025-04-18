#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<int>>dp(rows,vector<int>(cols,INT_MAX));
        for(int i = 0; i < rows; i++){
            for(int j = 0; j< cols; j++){
                if(i==0){
                    dp[i][j] = grid[i][j];
                }
                else{
                    int left = -1, right = -1;
                    if(j-1>=0){
                        left = dp[i-1][j-1];
                        dp[i][j] = left;
                    }
                    if(j+1<cols){
                        right = dp[i-1][j+1];
                        dp[i][j] = min(right,dp[i][j]);
                    }
                    dp[i][j] += grid[i][j];
                }
            }
        }
       int max_value = -1;
        for(int i = 0; i < cols; i++){
            if(i==0){
                max_value = dp[rows-1][0];
            }
            else{
                max_value = min(max_value,dp[rows-1][i]);
            }
        }
        return max_value; 
}
};
int main(){
    vector<vector<int>> grid ={{2,2,1,2,2},{2,2,1,2,2},{2,2,1,2,2},{2,2,1,2,2},{2,2,1,2,2}} ; 
    Solution A ;
    int ans =A.minFallingPathSum(grid);
    cout<<ans<<endl;
}