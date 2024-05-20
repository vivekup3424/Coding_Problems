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
// Custom hash function for pairs
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const
    {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1); // Combining the hashes
    }
};
struct tuple_hash
{
    template <class T1, class T2, class T3>
    std::size_t operator()(const std::tuple<T1, T2, T3> &tuple) const
    {
        auto hash1 = std::hash<T1>{}(std::get<0>(tuple));
        auto hash2 = std::hash<T2>{}(std::get<1>(tuple));
        auto hash3 = std::hash<T3>{}(std::get<2>(tuple));
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2); // Combining the hashes
    }
};
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        vll a(n);
        inputVector(a, n);
        unordered_map<pair<int, int>, vector<int>, pair_hash> pref, middle, suff;
        unordered_map<tuple<int, int, int>, vector<int>, tuple_hash> tripletMap;
        // generating middles
        for (int i = 2; i < n; i++)
        {
            int p = a[i - 2];
            int q = a[i - 1];
            int r = a[i];
            tripletMap[{p, q, r}].push_back(i - 2);
        }
        vector<int> num_equals(n, 0);
        for (auto it : tripletMap)
        {
            int s = it.second.size();
            for (int i = 0; i < s; i++)
            {
                num_equals[it.second[i]] = s;
            }
        }
        {
            // Optional: Print the map for verification
            cout << "Triplet Map:" << endl;
            for (const auto &entry : tripletMap)
            {
                cout << "(" << get<0>(entry.first) << ", " << get<1>(entry.first) << ", " << get<2>(entry.first) << "): ";
                for (int idx : entry.second)
                {
                    cout << idx << " ";
                }
                cout << endl;
            }
        }
        // getting the unique triplets
        for (auto it : tripletMap)
        {
            int idx = it.second.front();
            int p = a[idx], q = a[idx + 1], r = a[idx + 2];
            pref[{q, r}].push_back(idx - 2);
            middle[{p, r}].push_back(idx - 2);
            suff[{p, q}].push_back(idx - 2);
        }
        {
            // Optional: Prjnt the maps for verification
            cout << "Prefix Map:" << endl;
            for (const auto &entry : pref)
            {
                cout << "(" << entry.first.first << ", " << entry.first.second << "): ";
                for (int idx : entry.second)
                {
                    cout << idx << " ";
                }
                cout << endl;
            }

            cout << "Middle Map:" << endl;
            for (const auto &entry : middle)
            {
                cout << "(" << entry.first.first << ", " << entry.first.second << "): ";
                for (int idx : entry.second)
                {
                    cout << idx << " ";
                }
                cout << endl;
            }

            cout << "Suffix Map:" << endl;
            for (const auto &entry : suff)
            {
                cout << "(" << entry.first.first << ", " << entry.first.second << "): ";
                for (int idx : entry.second)
                {
                    cout << idx << " ";
                }
                cout << endl;
            }
        }
        int sum = 0;
        for (auto it : pref)
        {
            int n = it.second.size();
            sum += (n * (n - 1)) / 2;
        }
        for (auto it : middle)
        {
            int n = it.second.size();
            sum += (n * (n - 1)) / 2;
        }
        for (auto it : suff)
        {
            int n = it.second.size();
            sum += (n * (n - 1)) / 2;
        }
        cout << sum << endl;
    }
}