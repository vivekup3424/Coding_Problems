#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, int n)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}
/**
 * The first line contains two integers n and m (1≤n≤2⋅105; 0≤m≤4⋅105

) — the number of communication towers and the number of wires, respectively.

Then n
lines follows, the i-th of them contains two integers li and ri (
    1≤li≤ri≤2⋅105) — the boundaries of the acceptable frequencies for the i

-th tower.

Then m
lines follows, the i-th of them contains two integers 
vi and ui (1≤vi,ui≤n; vi≠ui) — the i-th wire that connects 
towers vi and ui. There are no two wires connecting the same pair of towers.
*/
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n,m;
        cin>>n>>m;
        vector<vector<int>> adj(n);
        vector<pair<int,int>> freq(n);
        for (int i = 0; i < n; i++)
        {
            ll l,r;
            cin>>l>>r;
            freq[i] = {l,r};
        }
        for (int i = 0; i < m; i++)
        {
            int a,b;
            cin>>a>>b;
            //1-index to 0-index
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }

        vector<int> ans;
        vector<int> visited(n,false);
        queue<pair<int, pair<int,int>>> q;
        q.push({0, freq[0]}); //first tower with compatibility
        while (q.empty()==false)
        {
            int t  = q.front().first;
            pair<int,int> range = q.front().second;
            q.pop();
            if(visited[t]==false){
                //new range
                ans.push_back(t+1);
                visited[0] = true;
            }
        }
        
        
    }
}
