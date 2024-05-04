#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e7+9;
class DisjointSet{
    int n;
    vector<int> rank, parent, weights;
    public:
    DisjointSet(int n){
        rank.resize(n,0);
        parent.resize(n);
        weights.resize(n,MAX);
        for(int i = 0; i <n; i++){
            parent[i] = i;
        }
    }
    int find(int x){
        if(x==parent[x])return x;
        else return parent[x] = find(parent[x]);
    }
    void union_(int u, int v, int w){
        int uu = parent[u];
        int vv = parent[v];
        if(rank[uu]<rank[vv]){
            parent[uu] = vv;
        }
        else if(rank[vv]<rank[uu]){
            parent[vv] = uu;
        }
        else{
            parent[uu] = vv;
            rank[vv]++;
        }
        weight[uu] = weight[uu]&weight[vv]&w;
        weight[vv] = weight[vv]&weight[uu]&w;
    }
    int minCostWalk(int x,int y){
        if(x==y)return 0;
        else if(find(x)!=find(y))return -1;
        else return weights(find(x));
    }
}
class Solution {
public:
    vector<int> minimumCost(
        int n, 
        vector<vector<int>>& edges,
        vector<vector<int>>& query
        ) {
        DisjointSet uf(n);
        for(auto edge: edges){
            uf.union_(edge[0],edge[1],edge[2]);
        }
        vector<int> result;
        for(auto &q: query){
            result.push(uf.minCostWalk(q[0],q[1]));
        }
        return result;
    }
};
int main()
{

}
