/*Given an array arr of lowercase strings, determine if 
 * the strings can be chained together to form a circle.
 * A string X can be chained together with another string Y 
 * if the last character of X is the same as the first character 
 * of Y. If every string of the array can be chained with exactly 
 * two strings of the array(one with the first character and the 
 * second with the last character of the string), it will form a
 * circle.*
 * */

#include <bits/stdc++.h>
using namespace std;

int isCircle(vector<string> &arr){
    int n = arr.size();
    vector<vector<int>> adj(n);
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(arr[i].back() == arr[j].front()){
                adj[i].push_back(j);
            }
            if(arr[j].back()==arr[i].front()){
                adj[j].push_back(i);
            }
        }
    }
    vector<int> v;
    //finding the length of cycle from 0 node
    queue<pair<int,int>> q; //{node, length}
    q.push({0,1});
    vector<bool> visited(n,false);
    while(q.size()>0){
        auto p = q.front();
        int node = p.first;
        int length = p.second;
        if(visited[node]){
            continue;
        }
        v.push_back(node);
        visited[node] = true;
        for (auto child : adj[node]) {
            q.push({child,length+1});
        }
    }
    for(int i:v){
        cout<<i<<"=>";
    }
    cout<<endl;
    return 1;
}
