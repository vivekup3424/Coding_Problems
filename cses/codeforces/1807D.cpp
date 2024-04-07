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
        ll n,q;
        cin>>n>>q;
        vll v(n);
        inputVector(v,n);
        vll prefixSum(n,v[0]);
        for(int i = 1; i < n; i++){
            prefixSum[i] = v[i] + prefixSum[i-1];
        }
        while(q--){
            ll l,r,k;
            cin>>l>>r>>k;
            l--;
            r--;
            ll total = prefixSum[n-1];
            ll leftOutSum = 0;
            if(l==0){
                leftOutSum = prefixSum[r];
            }
            else{
                leftOutSum = prefixSum[r] - prefixSum[l-1];
            }
            ll addedSum = (r-l+1)*k;
            if((total - leftOutSum + addedSum)%2==1){
                cout<<"YES\n";
            }
            else{
                cout<<"NO\n";
            }
        }
    }
}
