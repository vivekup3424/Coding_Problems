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
        ll n;
        cin>>n;
        vll v(n);
        inputVector(v,n);
        vector<pair<int,int>> paths;
        int idx = -1;
        for (int i = 0; i < n; i++)
        {
            if(v[i]!=v[0]){
                idx = i;
                paths.push_back({1,i+1});
            }
        }
        if(idx==-1){
            cout<<"NO"<<endl;
            continue;
        }
        for(int i = 0; i < n; i++){
            if(v[i]==v[0]){
                paths.push_back({idx+1,i+1});
            }
        }
        cout<<"YES"<<endl;
        for(auto [x,y]: paths){
            cout<<x<<" "<<y<<endl;
        }
    }
}
