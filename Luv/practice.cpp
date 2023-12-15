#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1;
vector<int> adj[N];
int dfs(int source, bool visited[], int N)
{
    visited[source] = true;
    for (auto child : adj[source])
    {
        if (visited[child])
            continue;
        dfs(child, visited, N);
    }
}
int main()
{
    int n, e;
    cin >> n >> e;
    for (auto i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int count = 0;
    bool visited[n + 10];
    memset(visited, false, n + 10);
    for (auto i = 1; i <= n; i++)
    {
        if (visited[i])
            continue;
        dfs(i, visited, N);
        count++;
    }
    cout << count << "\n";
}