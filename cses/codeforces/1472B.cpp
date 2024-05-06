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
        int count1 = 0, count2 = 0;
        for (int i = 0; i < n; i++)
        {
            ll temp;
            cin >> temp;
            if (temp == 1)
            {
                count1++;
            }
            else if (temp == 2)
            {
                count2++;
            }
        }
        int a = 0, b = 0;
        // distributing the elements
        int l1 = count2 / 2;
        int l2 = count2 - l1;
        a += 2 * l1;
        b += 2 * l2;
        if (b > a)
        {
            // first equalize a
            if (count1 >= b - a)
            {
                count1 -= b - a;
                a = b;
            }
            a += count1 / 2;
            b += (count1 - count1 / 2);
        }
        cout << a << ", " << b << endl;
    }
}