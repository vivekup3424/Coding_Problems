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
int minCost(int num, int cost, int minSteps){
    if(num==0){
        minSteps = min(cost, minSteps);
        return minSteps;
    }
    string n = to_string(num);
    for(int i = 0;i < n.length(); i++){
        num = num - (n[i] + '0');
        
    }
}
int main()
{
    fast_io();
    ll n;
    cin>>n;
    cout<<minCost(n,0,INT_MAX)<<endl;
}
