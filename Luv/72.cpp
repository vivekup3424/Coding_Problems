// How To Solve Graph Matrix Problems using DFS
//| Leetcode Flood Fill
//| CP Course | EP 72

#include <bits/stdc++.h>
using namespace std;
void dfs(int i, int j, vector<vector<int>> &image, int initialColor, int newColor)
{
    int n = image.size(); // image has a dimension of nxm
    int m = image[0].size();
    if (i < 0 or j < 0 or i >= n or j >= m or image[i][j] != initialColor)
        return;
    image[i][j] = newColor;
    dfs(i - 1, j, image, initialColor, newColor);
    dfs(i + 1, j, image, initialColor, newColor);
    dfs(i, j - 1, image, initialColor, newColor);
    dfs(i, j + 1, image, initialColor, newColor);
}
vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
{
    int initialColor = image[sr][sc];
    if (initialColor != color)
    {
        dfs(sr, sc, image, initialColor, color);
    }
    return image;
}
int main()
{
}