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

int main()
{
    fast_io();
    ll T = 1;
    while (T--)
    {
        ll N;
        cin>>N;
       vector<int> hashMap(26,0);
       for (int i = 0; i < N; i++)
       {
        string s;
        cin>>s;
        vector<int> freq(26,0);
        for(char c: s){
            if('a'<=c and c<='z'){
                freq[c-'a']++;        
            }
        }
        for (int i = 0; i < 26; i++)
        {
            hashMap[i] = max(hashMap[i],freq[i]);
        }
       }
       for (int i = 0; i < 26; i++)
       {
        cout<<hashMap[i]<<endl;
       }
       
    }
}