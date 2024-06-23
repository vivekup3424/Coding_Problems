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
    lli n,m,a;
    cin>>n>>m>>a;
    lli t1,t2;
    t1 = (n % a == 0) ? n/a : (n+a)/a;
    t2 = (m % a == 0) ? m/a : (m+a)/a;
    cout<< t1 * t2;
}