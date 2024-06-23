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
    int n;
    cin>>n;
    vector<lli> c(n,0);
    for(int i = 0; i<n;i++)
    {
        cin>>c[i];
    }
    lli upper_bound = INT_MAX;
    lli sum = 0;
    for(int i = n-1;i >=0;i--){
        upper_bound = min(upper_bound-1,c[i]);
        if(upper_bound < 0)upper_bound = 0;
        sum += upper_bound;
    }
    cout<<sum<<endl;
}