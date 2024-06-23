
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<vector<int>> dp[N];
class Solution
{
public:
    void dfs(vector<vector<int>> &adj, vector<bool> visited, int source, int parent)
    {
        visited[source] = true;
        for (auto child : adj[source])
        {
            if (visited[child] == true and child != parent)
                continue;
            else
            {
                dfs(adj, visited, child);
            }
        }
    }
    vector<int> countVisitedNodes(vector<int> &edges)
    {
        int n = edges.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++)
        {
            adj[i].push_back(edges[i]);
        }
    }
};
int main()
{
}