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
    float h,l;
    cin>>h>>l;
    float ans = ((l * l) - (h * h))/ (2*h);
    cout<<ans<<endl;
}