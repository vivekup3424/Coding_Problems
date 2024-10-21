class Solution {
private:
    const int LAND = 1;
    const int WATER = 0;
    const int VISITED = 2;
    void exploreLand(int x, int y, vector<vector<int>>& grid, int& perimeter) {
        int n = grid.size();
        int m = grid[0].size();
        if (x < 0 || y < 0 || x >= n || y >= m || grid[x][y] == WATER) {
            perimeter++;
            return;
        }
        if (grid[x][y] == VISITED) {
            return;
        }
        grid[x][y] = VISITED;
        exploreLand(x - 1, y, grid, perimeter);  // Up
        exploreLand(x + 1, y, grid, perimeter);  // Down
        exploreLand(x, y - 1, grid, perimeter);  // Left
        exploreLand(x, y + 1, grid, perimeter);  // Right
    }

public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == LAND) {
                    exploreLand(i, j, grid, perimeter);
                    return perimeter;
                }
            }
        }
        return perimeter;
    }
};
