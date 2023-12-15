
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    void dfs(int src, vector<vector<int>> &g, int *count, int *maxCount)
    {
        if (visited[src])
            return;
        visited[src] = true;
        (*count)++; // increment the count after visiting one node
        for (auto child : g[src])
        {
            dfs(child, g, count, maxCount);
        }
        *maxCount = max(*count, *maxCount);
    }
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int maxCount = 0;
        int m = grid.size();
        for (int i = 0; i < m; i++)
        {
            int temp = 0;
            dfs(i, grid, &temp, &maxCount);
        }
        return maxCount;
    }
};
int main()
{
}