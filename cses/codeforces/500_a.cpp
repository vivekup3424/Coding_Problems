
#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &adj, vector<bool> &visited, int src, int dest, bool &result)
{
    if (src == dest)
    {
        result = true;
        return;
    }
    else if (visited[src])
    {
        return;
    }
    else
    {
        visited[src] == true;
        for (auto child : adj[src])
        {
            dfs(adj, visited, child, dest, result);
        }
    }
}
int main()
{
    int n, t;
    cin >> n >> t;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int ai;
        cin >> ai;
        adj[i].push_back(i + ai);
    }
    vector<bool> visited(n + 1, false);
    bool res = false;
    dfs(adj, visited, 1, t, res);
    cout << (res ? "YES" : "NO") << endl;
    return 0;
}