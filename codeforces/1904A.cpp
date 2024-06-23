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

int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll a,b;
        cin>>a>>b;
        ll x1,y1,x2,y2;
        cin>>x1>>y1;
        cin>>x2>>y2;
        set<pair<ll,ll>> moves = {{a,b},{-a,b},{a,-b},{-a,-b},{b,a},{-b,a},{b,-a},{-b,-a}};
        pair<ll,ll> A = {x1,y1};
        pair<ll,ll> B = {x2,y2};
        ll count = 0;
        set<pair<ll,ll>> locations;
        for(auto p : moves){
            pair<ll,ll> point = {A.first + p.first, A.second+p.second};
            pair<ll,ll> movement = {point.first - B.first,point.second - B.second};
            if(moves.find(movement)!=moves.end()){
                locations.insert(point);
            }
        }
        cout<<locations.size()<<endl;
    }
}
