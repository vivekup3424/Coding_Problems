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
        vll c(n);
        inputVector(c, n);
        sort(c.begin(), c.end());
        vector<int> temp;
        // get the set of all unique elements in c
        set<int> st;
        for (int num : c)
        {
            st.insert(num);
        }
        if (st.count(1) == 0)
        {
            cout << "NO";
            continue;
        }
        for (auto it : st)
        {
            temp.push_back(it);
        }
        // check if using these integers whether I can get all
        // all the integers in c or not
    }
}