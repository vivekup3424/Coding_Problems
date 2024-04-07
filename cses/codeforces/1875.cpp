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
void inputVector(vector<T> &v, int n=0)
{
    if(n==0)n = v.size();
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n = 0)
{
    if(n==0)n = v.size();
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
        ll a,b,n;
        cin>>a>>b>>n;
        vll v(n);
        inputVector(v);
        ll totalTime = 0;
        totalTime += (b-1);
        for (ll i = 0; i < n; i++)
        {
            ll m = min(a, 1 + v[i]);
            totalTime += (m-1);
        }
        totalTime+=1;
        cout<<totalTime<<endl;
    }
}
