#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>> &grid, int x, int y){
        int rows = grid.size();
        int cols = grid[0].size();
        if(x < 0 || y < 0 || x>= rows || y >= cols || grid[x][y] == '0'){
            return;
        }
        grid[x][y] = '0';
        dfs(grid,x-1,y);
        dfs(grid,x+1,y);
        dfs(grid,x,y-1);
        dfs(grid,x,y+1);
    }
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        int count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if(grid[i][j]=='1'){
                    count++;
                    dfs(grid,i,j);
                }
            } 
        }
        return count;
    }
};
