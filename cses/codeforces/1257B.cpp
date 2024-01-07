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
    while (T--)
    {
        lli x,y;
        cin>>x>>y;
        if(y==1)cout<<"YES\n";
        else if(x==1 and y != 1)cout<<"NO\n";
        else if(x==2 || x==3){
            if(y==2 || y ==3)cout<<"YES\n";
            else cout<<"NO\n";
        }
        else cout<<"YES\n";
    }
}