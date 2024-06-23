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
     int n,m;
     cin>>n>>m;
     string a,b;
     cin>>a>>b;
     if(n<m)cout<<"NO\n";
     else{
        //check for the suffix with length m-1;
        bool same = true;
        for(int i = m-1, j = n-1; i > 0; i--,j--){
            if(b[i]==a[j])continue;
            else{
                same = false;
                break;
            }
        }
        if(same == false){
            cout<<"NO\n";
            continue;
        }
        bool firstmatch = false;
        for(int i = 0; i < n-m+1;i++){
            if(a[i]==b[0]) {
                firstmatch = true;
                break;
            }
        }
        if(firstmatch)cout<<"YES\n";
        else cout<<"NO\n";
     }
        
    }
}
