#include <bits/stdc++.h>
using namespace std;
const int INF = 1e5+7;
int timer = 1;
class Solution {
public:
    void dfs(vector<vector<int>> &adj,int node, int parent, vector<bool> &visited, vector<int> &time,vector<int> &low, vector<vector<int>> &bridges){
        visited[node] = true;
        time[node] = timer;
        low[node] = min(low[node], timer);
        timer++;
        for(auto child: adj[node]){
            if(child == parent)continue;
            else if(visited[child]==false){
                dfs(adj,child,node,visited,time,low);
                low[node] = min(low[node], low[child]);
                if(low[child] <= low[node]){
                    //child can reach node
                }
                else if(low[child]> low[node]){
                    //child can reach node
                    bridges.push_back({node, child});
                }
            }
            else {
                low[node] = min(low[node], low[child]);
            }
        }
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for(auto it: connections){
            adj[it.front()].push_back(it.back());
            adj[it.back()].push_back(it.front());
        }
        vector<int> low(n,INF);
        vector<bool> visited(n, false);
        vector<int> time(n,INF);
        vector<vector<int>> bridges;
        dfs(adj,0,-1,visited,time,low,bridges);
    }
};
int main(){

}