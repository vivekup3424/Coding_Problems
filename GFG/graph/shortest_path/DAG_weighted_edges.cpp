#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> weightedAdjacencyList(int nodes,vector<vector<int>> edges){
    //edges = {a,b,w} a = source, b = destination, w = weight of edge
    vector<vector<pair<int,int>>> adjList(nodes);
    for(int i = 0; i < edges.size();i++){
        int src = edges[i][0];
        int dest = edges[i][1];
        int weight = edges[i][2];
        adjList[src].push_back({dest, weight});
    };
    return adjList;
}
vector<int> topologicalSort(vector<vector<pair<int,int>>> adjList, int nodes){
    vector<int> indegree(nodes,0);
    for(int i = 0;i < nodes; i++){
        for(auto j : adjList[i]){
            int vertex = j.first;
            indegree[vertex]++;
        }
    }
    queue<int> q;
    for(int i = 0; i < nodes; i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    vector<int> topo;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        topo.push_back(node);
        for(auto edge : adjList[node]){
            int dest = edge.first;
            indegree[dest]--;
            if(indegree[dest]==0)q.push(dest);
        }
    }
    return topo;
}
