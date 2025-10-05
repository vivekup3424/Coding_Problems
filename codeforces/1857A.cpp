#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin>>a[i];
    }
    int totalSum = accumulate(a.begin(), a.end(), 0);
    if(totalSum&1){
        cout<<"NO"<<endl;
    }
    int currentSum = 0;

}