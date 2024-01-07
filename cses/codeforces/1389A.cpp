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
        int l,r;
        cin>>l>>r;
        int LCM = 2 * l;
        if(LCM <=r){
            cout<<l<<" "<<LCM<<endl;
        }
        else{
            cout<<"-1 -1\n";
        }
        
    }
}