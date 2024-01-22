#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi; 
const ll MAX = 2e5+4;
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
    string s;
    for(int i = 0;i < MAX;i+=4){
        s += "bb";
        s += "aa";
    }
    cout<<s.substr(0,T)<<endl;
}
//definitely take twosdfsfd