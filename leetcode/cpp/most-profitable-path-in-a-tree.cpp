#include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
    int mostProfitablePath(vector<vector<int>> &edges, int bob, vector<int> &amount){
        //construct the graph
        map<int,set<int>> graph;
        for(auto edge: edges){
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
        //do a bfs for bob to go to root(0)
        //since his only objective is to reach 0 ASAP
        vector<int> shortestPathForBob;
        queue<int> q;
        q.push(bob);
        while(q.size()>0){
           whabtjba 
        }
    }
};