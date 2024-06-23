#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
typedef std::vector<int> vi; 

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
       int n;
       cin>>n;
       string s;
       cin>>s;
       if(n==1 ||(n==2 and s[0]!=s[1]))cout<<"YES\n";
       else cout<<"NO\n";
    }
}