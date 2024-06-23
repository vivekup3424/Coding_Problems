#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>> &mat, int i, int j){
        int rows = mat.size();
        int cols = mat[0].size();
        if(i<0 or j<0 or i>=rows or j>=cols or mat[i][j]==0){
            return;
        }
        mat[i][j] = 0;
        dfs(mat,i,j+1);
        dfs(mat,i+1,j);
        dfs(mat,i-1,j);
        dfs(mat,i,j-1);
    }
    int numEnclaves(vector<vector<int>>& grid) {
        vector<vector<int>> mat = grid;
        int rows = mat.size(), cols = mat[0].size();
        //first row and last row
        for(int j = 0; j<cols; j++){
            if(mat[0][j]==1){
                dfs(mat,0,j);
            }
            if(mat[rows-1][j]==1){
                dfs(mat,rows-1,j);
            }
        }
        //first column amd last column
        for(int j = 0; j<rows; j++){
            if(mat[j][0]==1){
                dfs(mat,j,0);
            }
            if(mat[j][cols-1]==1){
                dfs(mat,j,cols-1);
            }
        }
        int count = 0;
        for(int i =0; i < rows; i++){
            for (int j = 0; j < cols ; j++)
            {
                if(mat[i][j]==1)count++;
            }
            
        }
        return count;
    }
};