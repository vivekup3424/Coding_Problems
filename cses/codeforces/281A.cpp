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
    if(s[0] >= 'a' and s[0]<='z')s[0] = s[0] + 'A' -'a';
    cout<<s<<endl;
}