//Cycle detection in directed graph can also be done using Kahn's algo with BFS
//Cycle detection can also be done using DFS

//this can also be called as cycle detection using topological sorting

//if using topological sort, the answer has less number of nodes,
//then we have a cycle

#include <bits/stdc++.h>
using namespace std;
int detectCycleInDirectedGraph(int n, vector < pair < int, int >> & edges) {
  vector<vector<int>> adj(n);
  for(auto edge: edges){
    adj[edge.first].push_back(edge.second);
  }
  vector<int> indegree(n,0);
  for(int i = 0; i < n;i++){
    for(auto it: adj[i]){
      indegree[it]++;
    }
  }

  queue<int> q;
  for(int i = 0; i < n;i++)
  {
    if(indegree[i]==0){
      q.push(i);
    }
  }

  vector<int> topo;
  while(q.empty()==false){
    int node = q.front();
    q.pop();
    topo.push_back(node);
    for(auto it :  adj[node]){
      indegree[it]--;
      if(indegree[it]==0)q.push(it);
    }
  }
  if(topo.size()==n)return false;
  else return true;
}