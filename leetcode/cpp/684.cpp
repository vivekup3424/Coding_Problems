
#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    void removeCycle(vector<vector<int>> &adj, vector<bool> &visited, int src, int parent, vector<int> &edge)
    {
        visited[src] = true;
        for (auto child : adj[src])
        {
            if (visited[child] == true)
            {
                if (child != parent)
                {
                    edge = {src, child};
                    return;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                removeCycle(adj, visited, child, src, edge);
            }
        }
    }
    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        // 1. do dfs traversal and when doing if in two nodes,
        // encountering a cycle then output that edge as to be removed
        int n = edges.size();
        vector<vector<int>> adj(n + 1);
        for (auto edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        vector<bool> visited(n, false);
        int src = 1, parent = 0;
        vector<int> edge;
        removeCycle(adj, visited, src, parent, edge);
        return edge;
    }
    // I was wrong in this question as I was not reading the question correctly, hence I need to do read questions correctly
};
class Solution
{
public:
    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        int n = edges.size();
        vector<int> set_representative(n + 1, 0);
        for (int i = 0; i < edges.size(); i++)
        {
            if (i == 0)
            {
                set_representative[edges[i][0]] = edges[i][0];
                set_representative[edges[i][1]] = edges[]
            }
        }
    }
};
int main()
{
}