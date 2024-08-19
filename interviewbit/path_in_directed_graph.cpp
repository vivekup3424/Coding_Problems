#include <bits/stdc++.h>
using namespace std;

void dfs(const vector<vector<int>> &adj, int source, vector<bool> &visited, vector<int> &v)
{
    if (visited[source])
    {
        return;
    }
    v.push_back(source);
    visited[source] = true;
    for (int neighbor : adj[source])
    {
        dfs(adj, neighbor, visited, v);
    }
}

int Solution::solve(int A, vector<vector<int>> &B)
{
    vector<vector<int>> adj(A + 1); // Adjacency list representation

    // Build the adjacency list from the edge list B
    for (const auto &edge : B)
    {
        adj[edge[0]].push_back(edge[1]);
    }

    vector<bool> visited(A + 1, false);
    vector<int> v;

    // Start DFS from node 1
    dfs(adj, 1, visited, v);

    // Check if node A is reachable
    for (int i : v)
    {
        if (i == A)
        {
            return 1; // Path exists
        }
    }
    return 0; // Path doesn't exist
}
