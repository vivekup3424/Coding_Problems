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
        ll max_ele = INT_MIN, min_ele = INT_MAX;
        for(int i = 0; i < n; i++){
            if(i>0){
                max_ele = max(max_ele,v[i]);
            }
            if(i!=n-1){
                min_ele= min(min_ele,v[i]);
            }
        }
        if(n==1){
            cout<<0<<endl;
        }
        else{
            cout<<max_ele- min_ele<<endl;
        }
    }
}
