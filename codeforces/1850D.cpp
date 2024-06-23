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
        sort(v.begin(),v.end());
        int currentLength = 1, maxLength = 1;
        int i = 1;
        while (i<n)
        {
            if((v[i] - v[i-1])<=k){
                currentLength++;
            }
            else{
                currentLength = 1;
                i++;
            }
            i++;
            maxLength = max(currentLength,maxLength);
        }
        cout<<maxLength<<endl;
    }
}
