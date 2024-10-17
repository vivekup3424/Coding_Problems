#include <bits/stdc++.h>
#include <numeric>
using namespace std;
int manhattan_distance(vector<int> &v1, vector<int> &v2){
    return abs(v1[0] - v2[0]) + abs(v1[1] - v2[0]);
}

int minCostConnectPoints(vector<vector<int>> points){
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> minHeap; //distance,index
    int n = points.size();
    vector<int> visited(n,false);
    vector<int> dist(n,INT_MAX);
    minHeap.push({0,0});
    visited[0] = true;
    dist[0]=0;
    while(minHeap.size()>0){
        auto [d,v] = minHeap.top();
        minHeap.pop();
        for(int i = 0; i < n; i++){
            int d1 = manhattan_distance(points[v],points[i]);
            if(visited[i]==false || dist[i]>(d+d1)){
                dist[i] = d + d1;
                visited[i] = true;
                minHeap.push({d+d1,i});
            }
        }
    }
    return accumulate(dist.begin(),dist.end(),0);
}
