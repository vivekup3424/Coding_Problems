#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi; 

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void dfs(vector<vector<ll>> &adjList, vector<bool> &visited,ll src, ll &vertices_count, ll &edgesCount){
    if(visited[src])return ;
    else{
        vertices_count++;
      visited[src] = true;
      for(ll i : adjList[src]){
        edgesCount++;
        dfs(adjList,visited,i,vertices_count,edgesCount);
      }
    }
}
int main()
{
    fast_io();
    ll n,m;
    cin>>n>>m;
    vector<vector<ll>> adj(n+1);
    for(ll i = 0;i < m;i++){
        ll  a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<bool> visited(n+1,false);
    //since this is a undirected graph, hence edge count would be 2 times that of average
    for(int i = 1;i <=n;i++){
        if(visited[i]==false){
            ll vertices = 0, edgeCount = 0;
            dfs(adj,visited,i,vertices,edgeCount);
            edgeCount /= 2;
            if(edgeCount != ((vertices)*(vertices-1))/2){
                cout<<"NO\n";
                return 0;
            }
        }
    }
    cout<<"YES\n";
    return 0;
}