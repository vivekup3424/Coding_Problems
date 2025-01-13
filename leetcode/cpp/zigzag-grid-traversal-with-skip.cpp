#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> zigzagTraversal(vector<vector<int>> grid)
    {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<int> result;
        for (int i = 0; i < rows; i++)
        {
            if (i % 2 == 0)
            {
                for (int j = 0; j < cols; j += 2)
                {
                    result.push_back(grid[i][j]);
                }
            }else{
                if(cols % 2 == 0){
                    for (int j = cols - 1; j >= 0; j -= 2)
                    {
                        result.push_back(grid[i][j]);
                    }
                }else{
                    for (int j = cols - 2; j >= 0; j -= 2)
                    {
                        result.push_back(grid[i][j]);
                    }
                }
        }
        return result;
    }
};