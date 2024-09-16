#include <bits/stdc++.h>
using namespace std;

class Solution{
void topoSort(vector<set<int>> adj){
        map<int,int> indegrees;
        for(int i = 0; i < adj.size(); i++){
            for(auto it: adj[i]){
                indegrees[it]++;
            }
        }
        vector<int> topo;
        vector<int> 
        
}
int solve(int A, vector<vector<int>> &B){
        vector<set<int>> adj;
        for(auto e : B){
            adj[e[0]].insert(e[1]);
        }
        return isCycle(adj);
    }
};

