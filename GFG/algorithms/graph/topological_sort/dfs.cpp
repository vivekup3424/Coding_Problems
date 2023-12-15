#include <bits/stdc++.h>
using namespace std;
void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &stk)
{
    if(visited[node]==true)
        return;
    else{
        visited[node] = true;
        for(int child : adj[node])
        {
            dfs(child,adj,visited, stk);
        }
        stk.push(node);
    }
}
vector<int> topologicalSort(vector<vector<int>> &graph, int edges, int nodes) {
    //building up adjacency matrix
    vector<vector<int>> adj(nodes);
    for(auto it : graph)
    {
        adj[it[0]].push_back(it[1]);
    }

    //topological sort
    stack<int> stk;
    vector<bool> visited(nodes, false);
    for(int i = 0; i < nodes; i++)
    {
        if(visited[i]==false)
        {
            dfs(i,adj,visited,stk);
        }
    }

    //building up the ordering
    vector<int> ans;
    while(stk.empty()==false)
    {
        ans.push_back(stk.top());
        stk.pop();
    }
    return ans;
}