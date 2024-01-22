#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
    ll T;
    cin >> T;
    while (T--)
    {
        int n;
        cin>>n;
        string a,b,c;
        cin>>a>>b>>c;
        bool result = false;
        for(int i = 0;i < n;i++){
                if(a[i]!=c[i] and b[i]!=c[i])
                {
                    cout<<"YES\n";
                    result = true;
                    break;
                }
            }
        if(result==false)cout<<"NO\n";
    }
}