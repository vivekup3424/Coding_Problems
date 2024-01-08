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
        string s;
        cin>>n;
        cin>>s;
        int sum = 0;
        for(char c : s){
            sum += c == '-' ? -1 : 1;
        }
        cout<<abs(sum)<<endl;
    }
}
