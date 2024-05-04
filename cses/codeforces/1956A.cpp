#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9+7;

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
ll lower_bound(vll &v, int a){
    ll l = 0, r = v.size()-1;
    ll lower = v.size();
    while(l<=r){
        ll mid = (l+r)/2;
        if(v[mid]<=a){
            lower = min(lower,mid);
            r = mid-1;
        }
        else if(v[mid]>a){
            r = mid-1;
        }
    }
    return lower;
}
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll k,q;
        cin>>k>>q;
        vll v(k);
        inputVector(v,k);
        ll smallest_guy = INT_MAX;
        for(auto i: v){
            smallest_guy = min(smallest_guy,i);
        }
        while(q--){
            ll temp;
            cin>>temp;
            if(temp < smallest_guy){
                cout<<temp<<" ";
            }
            else{
                cout<<smallest_guy-1<<" ";
            }
        }
        cout<<endl;
    }
}