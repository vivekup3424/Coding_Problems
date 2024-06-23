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
        unordered_map<lli,lli>paths;
        lli maxElement = 0;
        int n ;
        cin>>n;
        for(int i = 0;i < n;i++){
            lli a, b;
            cin>>a>>b;
            paths[a] = b;
            maxElement = max(maxElement, max(abs(a),abs(b)));
        }
        vector<int> v(2 * maxElement + 1,0);
        for(auto it : paths){
            v[it.first + maxElement] = 1;
            v[it.second+maxElement+1] = -1;
        }
        //sweep line algo
        int sum_collisions = 0;
        for(int i  = 1; i < v.size(); i++){
            v[i] += v[i-1];
            if(v[i]>1){
                sum_collisions += v[i] - 1;
            }
        }
        cout<<sum_collisions<<endl;
    }
}
