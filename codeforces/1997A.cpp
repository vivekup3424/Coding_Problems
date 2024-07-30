#include <bits/stdc++.h>
using namespace std;

// Type definitions
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;

// Fast I/O setup
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements into a vector
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

int main(int argc, char const *argv[])
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        string s;
        cin >> s;
        int n = s.size();
        int ans = -1;
        for (int i = 0; i < n - 1; i++)
        {
            if (s[i] == s[i + 1])
            {
                ans = i + 1;
                break;
            }
        }
        string temp;
        if (ans == -1)
        {
            temp += s;
            for (char c = 'a'; c <= 'z'; c++)
            {
                if (c != s[n - 1])
                {
                    temp.push_back(c);
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < ans; i++)
            {
                temp.push_back(s[i]);
            }
            for (char c = 'a'; c <= 'z'; c++)
            {
                if (c != temp.back())
                {
                    temp.push_back(c);
                    break;
                }
            }
            for (int i = ans; i < n; i++)
            {
                temp.push_back(s[i]);
            }
        }
        cout << temp << endl;
    }

    return 0;
}