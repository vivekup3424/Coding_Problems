#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
typedef std::vector<int> vi;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
int dp
void dfs(int node,int parent = -1, int level = 0){
    
}
int main()
{
    fast_io();
    int n;
    cin>>n;
    vector<vector<int>> adj(n);
    for(int i = 0;i < n;i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> leaves;
    int root = 1;
    for(int i = 1; i <=n;i++){
        if(adj[i].size()==1)leaves.push_back(i);
        else root = i;
    }

}