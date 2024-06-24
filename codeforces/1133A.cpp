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
string convert(int t)
{
    string temp = to_string(t);
    if (temp.length() == 1)
    {
        temp = "0" + temp;
    }
    return temp;
}
int main()
{
    fast_io();
    ll T = 1;
    while (T--)
    {
        char c;
        ll h1, m1;
        cin >> h1 >> c >> m1;
        ll h2, m2;
        cin >> h2 >> c >> m2;
        ll h, m;
        m = (m1 + m2) / 2;
        h = (h1 + h2) / 2;
        if ((h1 + h2) % 2 != 0)
        {
            m += 30;
        }
        if (m >= 60)
        {
            m %= 60;
            h++;
        }
        cout << convert(h) << ":" << convert(m) << endl;
    }
}