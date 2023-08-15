// You are given a map of a labyrinth, and your task is to
// find a path from start to end. You can walk left, right, up and down

// This is easy, I can use dfs to find the path from start to finish
// I can consider the matrix as a graph
#include <bits/stdc++.h>
using namespace std;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
#define MAX 1000
int vis[MAX + 10][MAX + 10];
char grid[MAX + 10][MAX + 10];
int n, m;
bool result = false;
int neighborX[4] = {0, 0, 1, -1};
int neighborY[4] = {1, -1, 0, 0};
bool isValid(int x, int y)
{
    if (x < 0 || y < 0 || x >= n || y >= m || grid[x][y] == '#')
        return false;
    return true;
}
void DFS(int x, int y)
{
    vis[x][y] = 1;
    if (grid[x][y] == 'B')
    {
        result = true;
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int newX = x + neighborX[i];
        int newY = y + neighborY[i];
        if (isValid(newX, newY) and !vis[newX][newY])
        {
            DFS(newX, newY);
        }
    }
}
int main()
{
    fast_io();
    cin >> n >> m;
    for (auto i = 0; i < n; i++)
    {
        for (auto j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }
}