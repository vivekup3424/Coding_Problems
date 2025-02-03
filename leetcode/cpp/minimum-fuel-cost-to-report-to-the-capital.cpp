#include <bits/stdc++.h>
#include <numeric>
#include <vector>
using namespace std;

class Solution{
public:
    long long minimumFuelCost(vector<vector<int>>&roads,int seats){
        map<int,int> distanceOfNodeFromZero;
        map<int,set<int>> graph;
        set<int> visited;
        for(auto road: roads){
            graph[road[0]].insert(road[1]);
            graph[road[1]].insert(road[0]);
        }
        queue<pair<int,int>> q;
        q.push({0,0});
        visited.insert(0);
        while(q.size()>0){
            auto [node,distance] = q.front();
            distanceOfNodeFromZero[node] = distance;
            q.pop();
            for(auto neighbor : graph[node]){
                if(!visited.count(neighbor)){
                    q.push({neighbor,distance+1});
                    visited.insert(neighbor);
                }
            }
        }
        //print out the distance of node from the root
        for(auto [node,distance] : distanceOfNodeFromZero){
            cout<<node<<" "<<distance<<endl;
        }
        return accumulate(distanceOfNodeFromZero.begin(),distanceOfNodeFromZero.end(),0);
    }
};
