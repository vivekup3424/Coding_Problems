#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumEffortPath(vector<vector<int>> &heights)
    {
        int rows = heights.size();
        int cols = heights[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        queue<vector<int>> q;
        int originx = 0, originy = 0;
        int targetx = rows - 1, targety = cols - 1;
        int minPath = INT_MAX;
        q.push({originx, originy, 0});
        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!q.empty())
        {
            vector<int> v = q.front();
            q.pop();
            int nodeX = v[0], nodeY = v[1], current_path = v[2];
            if (nodeX == targetx && nodeY == targety)
            {
                minPath = min(minPath, current_path);
            }
            visited[nodeX][nodeY] = true; // Mark the current cell as visited

            for (auto dir : directions)
            {
                int newX = nodeX + dir[0];
                int newY = nodeY + dir[1];
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                    !visited[newX][newY])
                {
                    int effort = abs(heights[nodeX][nodeY] - heights[newX][newY]);
                    q.push({newX, newY, max(current_path, effort)});
                }
            }
        }
        return minPath;
    }
};
