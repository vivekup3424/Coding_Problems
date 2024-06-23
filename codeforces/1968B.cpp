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
        ll n, m;
        cin >> n >> m;
        string a, b;
        cin >> a >> b;
        vector<pair<ll, ll>> count_a(n), count_b(m);
        for (int i = n - 1; i >= 0; i--)
        {
            if (i == n - 1)
            {
                if (a[i] == '1')
                {
                    count_a[i] = {0, 1};
                }
                else
                {
                    count_a[i] = {1, 0};
                }
            }
            else
            {
                if (a[i] == '1')
                {
                    count_a[i] = {0 + count_a[i + 1].first,
                                  1 + count_a[i + 1].second};
                }
                else
                {
                    count_a[i] = {1 + count_a[i + 1].first,
                                  0 + count_a[i + 1].second};
                }
            }
        }
        for (int i = m - 1; i >= 0; i--)
        {
            if (i == m - 1)
            {
                if (b[i] == '1')
                {
                    count_b[i] = {0, 1};
                }
                else
                {
                    count_b[i] = {1, 0};
                }
            }
            else
            {
                if (b[i] == '1')
                {
                    count_b[i] = {0 + count_b[i + 1].first,
                                  1 + count_b[i + 1].second};
                }
                else
                {
                    count_b[i] = {1 + count_b[i + 1].first,
                                  0 + count_b[i + 1].second};
                }
            }
        }

        // printing the count A
        for (int i = 0; i < count_a.size(); i++)
        {
            cout << count_a[i].first << " " << count_a[i].second << endl;
        }
        cout << "_________________________________________\n";
        for (int i = 0; i < count_b.size(); i++)
        {
            cout << count_b[i].first << " " << count_b[i].second << endl;
        }
        cout << "==============================\n";

        // now comes the major calculation
        int count0 = count_b[0].first;
        int count1 = count_b[1].second;
        int length = 0;
        bool stop = false;
        while (!stop)
        {
            cout << "Count 0 =" << count0 << ", Count1 = " << count1 << endl;
            if (a[length] == '1')
            {
                if (count1 > 0)
                {
                    count1--;
                    length++;
                }
                else
                {
                    stop = true;
                }
            }
            else if (a[length] == '0')
            {
                if (count0 > 0)
                {
                    count0--;
                    length++;
                }
                else
                {
                    stop = true;
                }
            }
        }
        cout << "Length = " << length << endl;
    }
}