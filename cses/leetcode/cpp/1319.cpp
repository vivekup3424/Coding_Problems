
#include <bits/stdc++.h>
using namespace std;
// Method 1: using dfs, self coded
class Solution
{
public:
    const static int N = 1e5 + 5;
    vector<int> adj[N];        // Adjacency list for graph representation
    bool visited[N] = {false}; // Array to keep track of visited nodes

    // Depth-First Search (DFS) traversal
    void dfs(int s)
    {
        if (visited[s])
        {
            return;
        }
        visited[s] = true;
        for (auto child : adj[s])
        {
            dfs(child);
        }
    }

    // Main function to make connected components
    int makeConnected(int n, vector<vector<int>> &con)
    {
        if (con.size() < n - 1)
        {
            return -1; // Not enough edges to connect all nodes
            // since for a graph of nodes n, atleast n edges are required to make it connected.
        }

        // Building the adjacency list from given connections
        for (auto edge : con)
        {
            int a = edge[0], b = edge[1];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        int count = 0; // Count of connected components
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == false)
            {
                count++;
                dfs(i); // Traverse the connected component using DFS
            }
        }

        return count - 1; // Number of redundant connections needed
    }
};
// Time complexity = O(V+E)
// SPpace Complexity O(V+E)
int main()
{
}