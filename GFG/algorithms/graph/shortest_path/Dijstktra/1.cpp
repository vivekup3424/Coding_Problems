#include <bits/stdc++.h>
using namespace std;

//Method 1:- Using priority queue
vector<int> dijsktra(int nodes, vector<vector<pair<int,int>>> &adj, int src){
    //note dijstktra does work when we have a negative edge present
    priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> minHeap;
    //minHeap stores {w,n} w -weight of the edge, n = incident node
    vector<int> distances(nodes, INT_MAX);
    distances[0] = 0;
    minHeap.push({0,src});
    while(!minHeap.empty()){
        int dist = minHeap.top().first;
        int node = minHeap.top().second;
        minHeap.pop();
        for(auto it: adj[node]){
            int edgeWeight = it.second;
            int adjNode = it.first;
            int pathLength = edgeWeight + dist;
            if(pathLength < distances[adjNode]){
                distances[adjNode] = pathLength;
                minHeap.push({pathLength, adjNode});
            }
        }
    }
    return distances;
    //Time Complexity = O(ElogV) //keep in mind the derivation.
}