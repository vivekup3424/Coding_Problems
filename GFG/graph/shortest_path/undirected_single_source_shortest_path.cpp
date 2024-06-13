#include <bits/stdc++.h>
using namespace std;
vector<int> shortestPath(int n, vector<vector<int>>&edges, int src) {
    //since this is a graph with uniform edges, hence I can use BFS for 
    //shortest path finding to all the nodes from source
    vector<vector<int>> adj(n);
    for(auto edge: edges)
    {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }
    //since there could be cycle, hence with BFS I need to make use of 
    vector<bool> visited(n, false);
    queue<pair<int,int>> q; //{node, distance}
    q.push({src,0});
    visited[src] = true; //mark source node as visited

    vector<int> distances(n,-1); //stores final answer
    
    while(!q.empty()){
        int node = q.front().first;
        int dist = q.front().second;
        distances[node] = dist; //important step
        q.pop();
        for(auto it: adj[node])
        {
            if(visited[it]==false)
            {
                visited[it] = true;
                q.push({it, dist+ 1});
            }
        }
    }
    return distances;
}