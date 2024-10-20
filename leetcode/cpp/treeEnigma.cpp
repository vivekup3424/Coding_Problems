#include <bits/stdc++.h>
using namespace std;
vector<vector<bool>> graph;
vector<int> start;
vector<int> target;
int result = 0;
int dfs(int root,bool inverted, int parent = -1){
    int cost = 0;
    if(inverted == false){
        cost = (start[root]!=target[root]);
    }else{
        cost = (!start[root] !=target[root]);
    }
    for(int i =0; i < graph.size(); i++){
        if(graph[root][i] and i != parent){
            cost += min(dfs(i,inverted,root), dfs(i,!inverted,root)+1);
        }
    }
    return cost;
}

int main(){
    int n,x,y;
    cin>>n>>x>>y;
    graph.resize(n,vector<bool>(n,false));
    start.resize(n,false);
    target.resize(n,false);
    for(int i = 0; i < n; i++){
        cin>>x>>y;
        graph[x-1][y-1] = 1;
        graph[y-1][x-1] = 1;
    }
    for(int i = 0; i <n; i++){
        cin>>start[i];
    }
    for(int i =0; i < n; i++){
        cin>>target[i];
    }
    cout<<min(dfs(0,false),dfs(0,true)+1)<<endl;
    return 0;
}
