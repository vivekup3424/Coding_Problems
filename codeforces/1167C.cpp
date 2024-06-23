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

class DisjointSet{
  ll n;
  vector<ll> rank, parent,size;
  public:
  //1-based indexing here. will also work for 0-indexing
  DisjointSet(ll n){
    n = n;
    rank.resize(n+1,0);
    parent.resize(n+1);
    size.resize(n+1,1); //initial size
    for(ll i = 0; i <= n;i ++){
      parent[i] = i;
    }
  }
  //find operation
  ll findUltimateParent(ll i){
    if(i == parent[i])return i;
    else return parent[i] = findUltimateParent(parent[i]); //path compression
  }
  //union by size
  void unionBySize(ll u, ll v){
    ll ult_parent_u = findUltimateParent(u);
    ll utl_parent_v = findUltimateParent(v);
    if(ult_parent_u == utl_parent_v)return;
    else if(size[ult_parent_u] < size[utl_parent_v]){
      parent[ult_parent_u] = utl_parent_v;
      size[utl_parent_v] += size[ult_parent_u];
    }
    else{
      parent[utl_parent_v] = ult_parent_u;
      size[ult_parent_u] += size[utl_parent_v];
    }
  }
    ll sizeOfGroup(ll i){
      ll parent = findUltimateParent(i); //finding parent with path compression
      return size[parent];
    }
};

int main()
{
    fast_io();
    ll n,m;
    cin>>n>>m;
    DisjointSet *D = new DisjointSet(n);
    for(int i = 0;i < m;i++){
        ll l;
        cin>>l;
        if(l==0){
            continue;
        }
        else if(l==0){
          ll redundant_node;
          cin>> redundant_node;
        }
        else{
            vector<ll> friends(l);
            for(ll i = 0;i <l;i++){
                cin>>friends[i];
            }
            for(ll i =1; i< l;i++){
                D->unionBySize(friends[i-1], friends[i]);
            }
        }
    }
    for(ll i = 1;i <=n;i++){
        cout<<D->sizeOfGroup(i)<<" ";
    }
    cout<<endl;
}