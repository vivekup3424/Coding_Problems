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
        ll n;
        cin>>n;
        //pick up the index of highest odd number
        int idx = 0;
        int max_odd_num = 0;
        for(int i = 0;i < n;i++){
            ll temp;
            cin>>temp;
            if(temp > max_odd_num){
                max_odd_num = temp;
                idx = i;
            }
        }
        cout<<idx+1<<endl;
    }
}