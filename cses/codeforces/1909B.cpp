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
        vector<lli> v(n,0);
        for(int i = 0; i < n;i++){
            cin>>v[i];
        }
        lli q = 2;
        while(true){
            set<lli> st;
            for(lli i : v){
                st.insert(i % q);
            }
            if(st.size()==2)break;
            else q = 2 * q;
        }
        cout<<q<<endl;
    }
}