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
        vector<ll> sides;
        ll a1, b1;
        cin>>a1>>b1;
        for(auto i = 0;i <3;i++){ //2-time
            ll a, b;
            cin>>a>>b;
            ll l = ((a-a1)*(a-a1) + (b-b1)*(b-b1));
            sides.push_back(l);
        }
        sort(sides.begin(),sides.end());
        ll product2 = sides[1] * sides[0];
        cout<<int(sqrt(product2))<<endl;
    }
}