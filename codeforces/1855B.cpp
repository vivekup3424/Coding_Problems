#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int t;
    cin>>t;
    while(t--){
        ll n;
        cin>>n;
        int count = 1;
        while(n%count==0){
            count++;
        }
        cout<<count-1<<endl;
    }
}