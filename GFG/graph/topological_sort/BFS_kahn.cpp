#include <bits/stdc++.h>
using namespace std;
vector<int> topologicalSort(vector<vector<int>> &graph, int edges, int nodes) {
    //create an adjacency matrix representation of graph
    vector<vector<int>> adj(nodes);
    for(auto edge: graph)
    {
        adj[edge[0]].push_back(edge[1]); 
    }
    //create an indegree array
    vector<int> indegree(nodes,0);
    for(auto edge : graph)
    {
        indegree[edge[1]]++;
    }
    queue<int> q;
    //using Kahn algo, choose nodes with indegree = 0
    for(int i = 0; i < nodes; i++)
    {
        if(indegree[i]==0){
            q.push(i);
        }
    }

    vector<int> topo;
    while(q.empty()==false)
    {
        int node = q.front();
        q.pop(); //FIFO
        topo.push_back(node);

        for(auto it: adj[node])
        {
            indegree[it]--;
            if(indegree[it]==0){
                q.push(it);
            }
        }
    }
    return topo;
}
