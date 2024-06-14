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
    int T = 1;
    while (T--)
    {
        int n, a, b, c;
        cin >> n >> a >> b >> c;
        vector<int> v(n + 1, 0);
        for (int i = 1; i < n + 1; i++)
        {
            int choice1 = 0, choice2 = 0, choice3 = 0;
            if (i - a > 0)
            {
                choice1 = v[i - a];
            }
            if (i - b > 0)
            {
                choice2 = v[i - b];
            }
            if (i - c > 0)
            {
                choice3 = v[i - c];
            }
            v[i] = max({choice1, choice2, choice3}) + 1;
        }
        std::cout << v.back() << endl;
    }
}