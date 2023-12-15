#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
#define MAX 1000
int neighborX[4] = {0, 0, 1, -1};
int neighborY[4] = {1, -1, 0, 0};
int vis[MAX + 10][MAX + 10];
char grid[MAX + 10][MAX + 10];
int n, m, counter = 0;
// if i imagine . as vertex and # as edges , i can solve this problem
// by the counting the connected components of a graph as one room
bool isValid(int x, int y)
{
    if (x < 0 || y < 0 || x >= n || y >= m || grid[x][y] == '#')
        return false;
}
void DFS(int x, int y) // DFS search for the node (x,y)
{
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++)
    {
        int newX = x + neighborX[i];
        int newY = y + neighborY[i];
        if (isValid(newX, newY))
        {
            if (!vis[newX][newY])
            {
                DFS(newX, newY);
            }
        }
    }
}
int main()
{
    fast_io();
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
            vis[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.' and !vis[i][j])
            {
                DFS(i, j);
                counter++;
            }
        }
    }
    cout << counter << "\n";
    return 0;
}