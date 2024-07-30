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
        ll n;
        cin >> n;
        vector<vector<char>> mat(2, vector<char>(n));
        string a, b;
        cin >> a >> b;
        for (int i = 0; i < n; i++)
        {
            mat[0][i] = a[i];
            mat[1][i] = b[i];
        }
        int count = 0;
        for (int i = 1; i < n - 1; i++)
        {
            // for above cells
            if (mat[0][i - 1] == '.' && mat[0][i + 1] == '.' && mat[1][i] == '.')
            {
                if (mat[1][i - 1] == 'x' && mat[1][i + 1] == 'x')
                {
                    count++;
                }
            }
            // for bottom cells
            if (mat[1][i - 1] == '.' && mat[1][i + 1] == '.' && mat[0][i] == '.')
            {
                if (mat[0][i - 1] == 'x' && mat[0][i + 1] == 'x')
                {
                    count++;
                }
            }
        }
        cout << count << endl;
    }
}