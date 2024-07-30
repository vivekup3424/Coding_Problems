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
    T = 1;
    while (T--)
    {
        string s;
        cin >> s;
        int A = 0, B = 0;
        int prev_A = 0, prev_B = 0;
        for (int i = 0; i < s.length(); i += 2)
        {
            char c = s[i];
            int v = s[i + 1] - '0';
            prev_A = A;
            prev_B = B;
            if (c == 'A')
            {
                A += v;
            }
            else
            {
                B += v;
            }
        }
        if (prev_A != prev_B)
        {
            if (A > B)
            {
                cout << "A" << endl;
            }
            else
            {
                cout << "B" << endl;
            }
        }
        else if (prev_A == prev_B)
        {
            if (A - B >= 2)
            {
                cout << "A" << endl;
            }
            else if (B - A >= 2)
            {
                cout << "B" << endl;
            }
        }
    }

    return 0;
}