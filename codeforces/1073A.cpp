#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
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
    string s;
    cin>>s;
    if(T==1){
        cout<<"NO"<<endl;
        return 0;
    }
    for(int i = 1; i < T; i++){
        if(s[i]!=s[i-1]){
            cout<<"YES"<<endl;
            cout<<s[i-1]<<s[i]<<endl;
            return 0;
        }
    }
    cout<<"NO"<<endl;
    return 0;
}