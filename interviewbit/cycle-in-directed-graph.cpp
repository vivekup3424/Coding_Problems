#include <bits/stdc++.h>
using namespace std;

class Solution{
vector<int> topoSort(vector<set<int>> adj){
        map<int,int> indegrees;
        for(int i = 0; i < adj.size(); i++){
            for(auto it: adj[i]){
                indegrees[it]++;
            }
        }
        vector<int> topo;
        queue<int> zeroInDegree;
        for(auto it: indegrees){
            if(it.second==0){
                zeroInDegree.push(it.first);
            }
        }
        while(zeroInDegree.size()>0){
            auto p = zeroInDegree.front();
            topo.push_back(p);
            for(auto i : adj[p]){
                indegrees[i]--;
                if(indegrees[i]==0){
                    zeroInDegree.push(i);
                }
            }
        }
        return topo;
}
int solve(int A, vector<vector<int>> &B){
        vector<set<int>> adj;
        for(auto e : B){
            adj[e[0]].insert(e[1]);
        }
        return A == topoSort(adj).size();
    }
};

