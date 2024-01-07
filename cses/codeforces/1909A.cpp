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
        int a = 1, b = 1, c = 1, d = 1;
        for(int i = 0;i < n;i++){
            int x,y;
            cin>>x>>y;
            if(x>0)a = 0;
            if(x<0) b = 0;
            if(y>0) c = 0;
            if(y<0) d = 0;
        }
        if(a+b+c+d > 0)cout<<"YES\n";
        else cout<< "NO\n";
    }
}