#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int row=grid.size();
        int col=grid[0].size();
        vector<vector<int>>visited(row,vector<int>(col,0));
        queue<pair<int,pair<int,int>>>q;
        int ans=0;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(grid[i][j]==2 && !visited[i][j]){
                    q.push({0,{i,j}});
                    visited[i][j]=1;
                }
            }
        }
        while(!q.empty()){
            int time=q.front().first;
            int _row=q.front().second.first;
            int _col=q.front().second.second;
            ans=max(ans,time);
            q.pop();
            int rw[]={-1,0,1,0};
            int cl[]={0,1,0,-1};
            for(int i=0;i<4;i++){
            int nrow=_row+rw[i];
            int ncol=_col+cl[i];
            if(nrow <row && nrow>=0 && ncol>=0 && ncol<col && !visited[nrow][ncol] && grid[nrow][ncol]==1){
                q.push({time+1,{nrow,ncol}});
                visited[nrow][ncol]=1;
            }
            }

        }
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(grid[i][j]==1 && visited[i][j]==0)
                    return -1;
            }
        }


        return ans;
    }
};
