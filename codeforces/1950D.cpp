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
void backtrack(int idx,int n,bitset<6> temp, vector<bitset<6>>&results){
    if(idx>=n){
        results.push_back(temp);
        return;
    }   
    temp[idx] = 1;
    backtrack(idx+1,n,temp,results);
    temp[idx] = 0;
    backtrack(idx+1,n,temp,results);
}
int main()
{
    fast_io();
    ll T=1;
    //std::cin >> T;
    while (T--)
    {
        ll n = 1e5;
        //generating the set of binary strings smaller than or equal
        // to n

        //I can use backtracking for this
        vector<bitset<6>> results;
        bitset<6> temp;
       backtrack(0,6,temp,results);
       vector<ulong> values;
       for(auto str: results){
        auto v = str.to_ulong();
        values.push_back(v);
       }
       //printout results
       //for(auto str: results){
       // cout<<str<<" ";
       //} 
       for(auto v: values){
        cout<<v<<" ";
       }
       cout<<endl;
    }
}