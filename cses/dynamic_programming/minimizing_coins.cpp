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
    ll T=1;
    while (T--)
    {
	ll n,x;
	cin>>n>>x;
    vll coins(n);
    inputVector(coins,n);
    vll dp(x+1,INT_MAX);
    for (int i = 1; i < n+1; i++)
    {       
        for (int j = 0; j < x+1; j++)
        {
            if(j==0)dp[j] = 0;
            else if(coins[i-1]<=j){
                dp[j] = min(dp[j], 1 + dp[j-coins[i-1]]);
            }
        }
    }
        cout<<(dp[x]==INT_MAX ? -1 : dp[x])<<endl;
    }
}
