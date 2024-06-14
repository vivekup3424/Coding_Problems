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
    int T;
    std::cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<int> v(n);
        inputVector(v, n);
        int sum = accumulate(v.begin(), v.end(), 0);
        if (sum & 1)
        {
            cout << "NO\n";
            continue;
        }
        else
        {
            ll required_sum = sum >> 1;
            bool dp[n + 1][required_sum + 1];
            for (int i = 0; i < n + 1; i++)
            {
                for (int j = 0; j < required_sum + 1; j++)
                {
                    if (i == 0)
                    {
                        dp[i][j] = false;
                    }
                    else if (j == 0)
                    {
                        dp[i][j] = true;
                    }
                    else if (v[i - 1] > required_sum)
                    {
                        dp[i][j] = dp[i - 1][j];
                    }
                    else
                    {
                        dp[i][j] = dp[i - 1][j - v[i - 1]] ||
                                   dp[i - 1][j];
                    }
                }
            }
            if (dp[n][required_sum] == true)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
}