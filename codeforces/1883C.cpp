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
        ll n,k;
        cin>>n>>k;
        vll v(n);
        inputVector(v,n);
        ll product = 1;
        for(ll i : v){
            product *= i;
        }
        bool isDivisible = false;
        if(product % k ==0){
            cout<<0<<endl;
        }
        else if(k==4){
            ll modOneCount = 0, modThreeCount = 0, modTwoCount = 0;
            for(ll i: v){
                if(i%k==3)modThreeCount++;
                else if(i%k==1)modOneCount++;
                else if(i%k==2)modTwoCount++;
            }
            if (modThreeCount > 0 || (modTwoCount > 0 && modOneCount > 0))
    cout << 1 << endl;
else if (modOneCount == 1 && modTwoCount == 0)
    cout << 3 << endl;
else if (modTwoCount == 1 && modOneCount == 0)
    cout << 3 << endl;
else
    cout << 2 << endl;

        }
        else{
            //get the max mod
            ll maxMod = 0;
            for(auto i : v){
                maxMod = max(maxMod, i%k);
            }
            cout<<k-maxMod<<endl;
        }
    }
}
