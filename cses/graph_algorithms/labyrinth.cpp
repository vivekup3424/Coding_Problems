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
int neighborX[4] = {0, 0, 1, -1}; //U,D,R,L
int neighborY[4] = {1, -1, 0, 0};
char directions[4] = {'U','D','R','L'};
bool isValid(vector<vector<char>> &grid,int x, int y, int n,int m)
{
    if (x < 0 || y < 0 || x >= n || y >= m || grid[x][y] == '#')
        return false;
    return true;
}
void dfs(vector<vector<char>> &grid,
        int x, int y, 
        vector<char> &path, 
        bool &result,
        vector<vector<bool>> &visited)
{
    int n = grid.size(), m = grid[0].size();
    visited[x][y] = true;
    if (grid[x][y] == 'B')
    {
        result = true;
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int newX = x + neighborX[i];
        int newY = y + neighborY[i];
        if (isValid(grid,newX, newY,n,m) and !visited[newX][newY])
        {
            path.push_back(directions[i]);
            dfs(grid,newX, newY,path,result,visited);
        }
    }
}
void bfs(vector<vector<char>> &grid,
        int x, int y, 
        queue<int,vector<int>> &q, 
        bool &result,
        vector<vector<bool>> &visited){
            q.push      
        }

int main()
{
    fast_io();
    int n,m;
    cin >> n >> m;
    vector<vector<char>> grid(n,vector<char>(m));
    for (auto i = 0; i < n; i++)
    {
        for (auto j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }
    vector<vector<bool>> visited(n,vector<bool>(m,false));
    bool result = false;
    vector<char> path;
    for (auto i = 0; i < n; i++)
    {
        for (auto j = 0; j < m; j++)
        {
            if(grid[i][j]=='A'){
                dfs(grid,i,j,path,result,visited);
            }
        }
    }
    if(result==true){
        cout<<"YES\n";
        cout<<path.size()<<endl;        for(char c: path){
            cout<<c;
        }
        cout<<endl;
    }
    else{
        cout<<"NO\n";
    }
}