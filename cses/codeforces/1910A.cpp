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
bool isNonZero(char c){
    if(c >= '1' and c <='9')return true;
    else return false;
}
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        string s;
        cin>>s;
        int n = s.size();
        for(int i  = n-1;i >=0; i--){
            if(isNonZero(s[i])){
                cout<<s.substr(0,i)<<endl;
                break;
            }
        }
    }
}