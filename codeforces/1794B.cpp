#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>v(n);
        for(int i = 0; i < n; i++){
            cin>>v[i];
        }
        for(int i = 0; i < n; i++){
            if(v[i]==1){
                v[i] = 2;
            }
        }
        for(int i = 0; i < n-1; i++){
            if(v[i+1]%v[i]==0){
                v[i+1]++;
            }
        }
        for(int i = 0; i < n; i++){
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }
}