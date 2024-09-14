#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isValid(int i, int j, int n, int m, set<pair<int,int>> visited){
        if(i< 0 || j <0 || i >= n || j >= m || visited.count({i,j})){
            return false;
        }
        return true;
    }
    bool dfs(vector<vector<int>> &grid,set<pair<int,int>> visited, int health, int i, int j, int n, int m){
        if(isValid(i,j,n,m,visited)==false){
            return false;
        }
        visited.insert({i,j});
        if(grid[i][j]==1){
            health--;
        }
        if(health>=1 and i == n-1 and j == m-1){
            return true;
        }
        return (dfs(grid,visited,health,i-1,j,n,m) || 
        dfs(grid,visited,health,i,j-1,n,m) || 
        dfs(grid,visited,health,i+1,j,n,m) || 
        dfs(grid,visited,health,i,j+1,n,m));
    }
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int n= grid.size(), m = grid[0].size();
        //do a dfs
        set<pair<int,int>> visited;
        return dfs(grid,visited,health,0,0,n,m);
    }
};
