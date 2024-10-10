#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dfs(vector<vector<int>> &grid, int x, int y){
        int rows = grid.size();
        int cols = grid[0].size();
        if(x < 0 || y < 0 || x>= rows || y >= cols || grid[x][y] == 0){
            return 0;
        }
        grid[x][y] = 0;
        return 1+
        dfs(grid,x-1,y)+
        dfs(grid,x+1,y)+
        dfs(grid,x,y-1)+
        dfs(grid,x,y+1);
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        int maxSum = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if(grid[i][j]==1){
                    maxSum = max(dfs(grid,i,j),maxSum);
                }
            } 
        }
        return maxSum;
    }
};

