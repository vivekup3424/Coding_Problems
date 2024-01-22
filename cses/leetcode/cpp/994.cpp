#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        queue<pair<pair<int,int>,int>> q; //coordinates to level or distance
        //in place of using visited matrix, just use the matrix grid from the question
        //but striver suggest to not change the data,hence lets make a visited matrix
        vector<vector<int>> visited(rows, vector<int>(cols,0));
        int count_fresh = 0; //count of fresh oranges
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < cols; j++){
                if(grid[i][j]==2){
                    q.push({{i,j},0}); //such a short hand its killing me
                    visited[i][j] = 2;
                }
                if(grid[i][j]){
                    count_fresh++;
                }
            }
        }
        vector<vector<int>> directions = {{0,1},
                                        {0,-1},
                                        {1,0},
                                        {-1,0}};
        //now do bfs
        int time = 0;
        while (!q.empty())
        {
            int x = q.front().first.first;
            int y = q.front().first.second;
            int level = q.front().second;
            time = max(time,level);
            q.pop();
            for(int i = 0;i < 4;i++){
                int x1 = x + directions[i][0];
                int y1 = y + directions[i][1];
                if(x1 < 0 or y1 < 0 or x1 >= rows or y1 >= cols or grid[x1][y1]!=1)continue;
                q.push({{x1,y1},level+1});
            }
        }
        //check for leftover fresh oranges
        for(int i = 0;i < rows;i++){
            for(int j = 0;j < cols;j++){
                if(grid[i][j]==1)return -1;
            }
        }
        return time;
    }
};