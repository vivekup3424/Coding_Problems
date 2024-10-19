#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int rows, cols;
public:
    int recurse(vector<vector<int>> &grid,int i, int j, int k){
        if(i==j || i < 0 || j < 0 || i >= cols || j >= cols){
            return 0;
        }else if(k==rows-1){
            return grid[i][k] + grid[j][k];
        }else{
            int dir[] = {-1,0,1};
            int maxi = INT_MIN;
            for(int di : dir){
                for(int dj : dir){
                    maxi = max(maxi, recurse(grid,i+di,j+dj,k+1));
                }
            }
            return maxi + grid[i][k] + grid[j][k];
        }
    }
    int cherryPickup(vector<vector<int>>& grid) {
        rows = grid.size();
        cols = grid[0].size();
        return recurse(grid,0,cols-1,0);
    }
};
