#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int i, int j,vector<pair<int,int>> &coordinates){
        int rows = grid.size();
        int cols = grid[0].size();
        if(i<0 or j <0 or i>=rows or j>= cols or 
        visited[i][j]==true or grid[i][j]==0){
            return ;
        }
        coordinates.push_back({i,j});
        visited[i][j] = true;
        dfs(grid,visited,i+1,j,coordinates);
        dfs(grid,visited,i,j+1,coordinates);
        dfs(grid,visited,i-1,j,coordinates);
        dfs(grid,visited,i,j-1,coordinates);
    }
    vector<vector<int>> findFarmland(vector<vector<int>>& land) {        
        int rows = land.size();
        int cols = land[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<vector<int>> answers;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                vector<pair<int,int>> coordinates;
                if(land[i][j]==1 and visited[i][j]==false){
                    dfs(land,visited,i,j,coordinates);
                    sort(coordinates.begin(),coordinates.end());
                    answers.push_back(
                        {coordinates.front().first, coordinates.front().second,coordinates.back().first, coordinates.back().second});
                }
            }   
        }
       return answers;
    }
};