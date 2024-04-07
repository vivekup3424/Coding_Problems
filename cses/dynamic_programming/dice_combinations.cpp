#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
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

int main()
{
    fast_io();
    ll T = 1;
    while (T--)
    {
        ll n;
        cin>>n;
        vll dp(n+1,0);
        dp[0] = 1;
        for(int i = 1; i<=n; i++){
            ll sum = 0;
            if(i-1>=0)sum =(sum + dp[i-1])%MOD;
            if(i-2>=0)sum =(sum + dp[i-2])%MOD;
            if(i-3>=0)sum =(sum + dp[i-3])%MOD;
            if(i-4>=0)sum =(sum + dp[i-4])%MOD;
            if(i-5>=0)sum =(sum + dp[i-5])%MOD;
            if(i-6>=0)sum =(sum + dp[i-6])%MOD;
            dp[i] = sum;
        }
        cout<<dp[n]<<endl;
    }
}
