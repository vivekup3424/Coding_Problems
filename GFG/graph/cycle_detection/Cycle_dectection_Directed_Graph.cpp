// Cycle detection in directed graph can also be done using Kahn's algo with BFS
// Cycle detection can also be done using DFS

// this can also be called as cycle detection using topological sorting

// if using topological sort, the answer has less number of nodes,
// then we have a cycle

#include <bits/stdc++.h>
using namespace std;
int detectCycleInDirectedGraph_topologicaal(int n, vector<pair<int, int>> &edges)
{
  vector<vector<int>> adj(n);
  for (auto edge : edges)
  {
    adj[edge.first].push_back(edge.second);
  }
  vector<int> indegree(n, 0);
  for (int i = 0; i < n; i++)
  {
    for (auto it : adj[i])
    {
      indegree[it]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < n; i++)
  {
    if (indegree[i] == 0)
    {
      q.push(i);
    }
  }

  vector<int> topo;
  while (q.empty() == false)
  {
    int node = q.front();
    q.pop();
    topo.push_back(node);
    for (auto it : adj[node])
    {
      indegree[it]--;
      if (indegree[it] == 0)
        q.push(it);
    }
  }
  if (topo.size() == n)
    return false;
  else
    return true;
}

/*Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges, check whether it contains any cycle or not.*/
bool detectCycle_BFS(int V, vector<int> adj[])
{
  bool containsCycle = false;
  vector<int> visited(V, false);
  for (int i = 0; i < V; i++)
  {
    if (visited[i] == false)
    {
      // do BFS
      queue<int> q;
      q.push(i);
      visited[i] = true;
      while (q.size() > 0)
      {
        int node = q.front();
        q.pop();
        for (int ch : adj[node])
        {
          if (visited[ch] == true)
          {
            containsCycle = true;
            return true;
          }
          else
          {
            q.push(ch);
            visited[ch] = true;
          }
        }
      }
    }
  }
  return false;
}