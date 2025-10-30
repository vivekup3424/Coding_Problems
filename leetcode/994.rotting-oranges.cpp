/*
 * @lc app=leetcode id=994 lang=cpp
 *
 * [994] Rotting Oranges
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        vector<vector<int>> temp = grid;
        int currentTime = 0, maxTime = 0;
        int totalOranges = 0;
        queue<pair<int,int>> q;
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                if(grid[i][j]!=0){
                    totalOranges+=1;
                }
                if(grid[i][j]==2){
                    q.push({i,j});
                }
            }
        }
        vector<pair<int,int>> directions = {{0,1}, {0,-1}, {1,0},{-1,0}};
        while(q.size()>0){
            auto [i,j] = q.front();
            q.pop();
            for(pair<int,int> direction : directions){
                pair<int,int> neighbor = {i+direction.first, j+ direction.second};
                if()
            }
        }
    }
};
// @lc code=end

