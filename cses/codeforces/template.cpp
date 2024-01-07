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
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        
        
    }
}

class DisjointSet{
  int n;
  vector<int> rank, parent,size;
  public:
  //1-based indexing here. will also work for 0-indexing
  DisjointSet(int n){
    n = n;
    rank.resize(n+1,0);
    parent.resize(n+1);
    size.resize(n+1,1); //initial size
    for(int i = 0; i <= n;i ++){
      parent[i] = i;
    }
  }
  //find operation
  int findUltimateParent(int i){
    if(i == parent[i])return i;
    else return parent[i] = findUltimateParent(parent[i]); //path compression
  }
  //union by size
  void unionBySize(int u, int v){
    int ult_parent_u = findUltimateParent(u);
    int utl_parent_v = findUltimateParent(v);
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
  //union operation
  void unionByRank(int u, int v){
    int ult_parent_u = findUltimateParent(u);
    int utl_parent_v = findUltimateParent(v);
    if(utl_parent_v == ult_parent_u)return ;
    else if(rank[ult_parent_u] < rank[utl_parent_v]){
      parent[ult_parent_u] = utl_parent_v;
    }
    else if(rank[utl_parent_v] < rank[ult_parent_u]) {
      parent[utl_parent_v] = ult_parent_u;
    }
    else{
      parent[utl_parent_v] = ult_parent_u;
      rank[ult_parent_u]++;
    }
  }
  //count number of components
   int countComponents(){
      int count = 0;
      for(int i = 0; i < n;i++){
        if(i == parent[i]){
          count++;
        }
      }
      return count;
    }
};

template <class T>
struct BIT { //1-indexed
  int n; vector<T> t;
  BIT() {}
  BIT(int _n) {
    n = _n; t.assign(n + 1, 0);
  }
  T query(int i) {
    T ans = 0;
    for (; i >= 1; i -= (i & -i)) ans += t[i];
    return ans;
  }
  void upd(int i, T val) {
    if (i <= 0) return;
    for (; i <= n; i += (i & -i)) t[i] += val;
  }
  void upd(int l, int r, T val) {
    upd(l, val);
    upd(r + 1, -val);
  }
  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
};

