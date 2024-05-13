#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> largestLocal(vector<vector<int>> &grid)
    {
        int center_x = 1, center_y = 1;
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<int>> answer;
        for (; center_x <= rows - 2; center_x++)
        {
            vector<int> temp;
            center_y = 1;
            for (; center_y <= cols - 2; center_y++)
            {
                int max_value = max({
                    grid[center_x - 1][center_y - 1],
                    grid[center_x - 1][center_y],
                    grid[center_x - 1][center_y + 1],
                    grid[center_x][center_y - 1],
                    grid[center_x][center_y],
                    grid[center_x][center_y + 1],
                    grid[center_x + 1][center_y - 1],
                    grid[center_x + 1][center_y],
                    grid[center_x + 1][center_y + 1],
                });
                temp.push_back(max_value);
            }
            answer.push_back(temp);
        }
        return answer;
    }
};