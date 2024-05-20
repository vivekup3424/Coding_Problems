#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;

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
        cin >> n;
        string b;
        cin >> b;
        vector<char> v;
        set<char> st;
        for (int i = 0; i < b.size(); i++)
        {
            char c = b[i];
            if (st.count(c) == 0)
            {
                v.push_back(c);
                st.insert(c);
            }
        }
        sort(v.begin(), v.end());
        unordered_map<char, char> mp;
        int i = 0, j = v.size()-1;
        while (i <= j)
        {
            mp[v[i]] = v[j];
            mp[v[j]] = v[i];
            i++;
            j--;
        }

        int len = v.size();
        for (int i = 0; i < b.size(); i++)
        {
            char c = b[i];
            b[i] = mp[c];
        }
        cout << b << endl;
    }
}