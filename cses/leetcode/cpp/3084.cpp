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
class Solution {
public:
    long long countSubstrings(string s, char c) {
        long long count = 0;
        for(char t: s){
            if(t==c)count++;
        }     
        long long ans = count;
        ans += (count*(count-1))/2;
        return ans;
    }
};
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        
    }
}
