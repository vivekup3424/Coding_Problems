#include <bits/stdc++.h>
using namespace std;
// Method 1: Thought by me.
class Solution
{
public:
	void dfs(int x, int y, vector<vector<int>> &grid, int landColor, int visited, int water, int *count)
	{
		int n = grid.size(), m = grid[0].size();
		if (x < 0 or y < 0 or x >= n or y >= m or grid[x][y] == water) // following the rules
		{
			(*count)++;
			return;
		}
		else if (grid[x][y] == visited)
		{
			return;
		}
		else
		{
			grid[x][y] = visited;
			dfs(x - 1, y, grid, landColor, visited, water, count);
			dfs(x, y - 1, grid, landColor, visited, water, count);
			dfs(x + 1, y, grid, landColor, visited, water, count);

			dfs(x, y + 1, grid, landColor, visited, water, count);
		}
	}
	int islandPerimeter(vector<vector<int>> &grid)
	{
		int rows = grid.size();
		int cols = grid[0].size();
		int land = 1, water = 0, visited = 2;
		int count = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j] == land)
				{
					dfs(i, j, grid, land, visited, water, &count);
					break;
				}
			}
		}
		return count;
	}
};
int main()
{
}
