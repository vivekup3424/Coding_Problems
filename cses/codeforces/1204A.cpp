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
    string s;
    cin>>s;
    int n = s.size();
    int counter = 0;
    for(char c: s){
        if(c=='1')counter++;
    }
    int ans = 0;
    if(counter == 1){
        ans = n/2;
    }
    else if(counter > 1) {
        ans = (n-1)/2;
        ans++;
    }
    cout<<ans<<endl;
}