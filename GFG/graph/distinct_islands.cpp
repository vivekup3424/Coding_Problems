#include <bits/stdc++.h>
using namespace std;

/**
 * Given a boolean 2D matrix. The task is to find the number of distinct islands where a group of 
 * connected 1s (horizontally or vertically) forms an island. Two islands are considered to be 
 * distinct if and only if one island is equal to another (not rotated or reflected).
*/


class Solution {
  public:
    const vector<vector<int>> directions = {{0,-1},
                                    {0,1},
                                    {1,0},
                                    {-1,0}};

    void dfs(vector<vector<int>> &grid, int x0, int y0, int i, int j, vector<pair<int,int>> &v){
        int rows = grid.size();
        int cols = grid[0].size();
        if(i<0 or j < 0 or i >= rows or j >= cols or grid[i][j] != 1)return ;
        //mark the cell as visited
        grid[i][j] *= -1;
        v.push_back({i-x0,j-y0});
        for(auto direction : directions){
            int i1 = i + direction[0];
            int j1 = j + direction[1];
            dfs(grid,x0,y0,i1,j1,v);
        }
    }
    int countDistinctIslands(vector<vector<int>>& grid) {
        int rows = grid.size();
        if(rows==0)return 0;
        int cols = grid[0].size();

        //I am going to do something very lazy and smart
        set<vector<pair<int,int>>> coordinates;
        for(int i = 0;i < rows;i++){
            for(int j = 0; j <  cols;j++){
                if(grid[i][j]==1){
                    vector<pair<int,int>> v;
                    dfs(grid, i,j,i,j,v);
                    coordinates.insert(v);
                }
            }
        }
        return coordinates.size();
    }
};