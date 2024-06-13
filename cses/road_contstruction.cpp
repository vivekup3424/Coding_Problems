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
class DSU
{
public:
    ll vertices;
    vll parents;
    vll size;
    ll components;
    ll maxSize;
    DSU(int n)
    {
        vertices = n;
        parents.resize(n + 1);
        for (int i = 0; i < n + 1; i++)
        {
            parents[i] = i;
        }
        size.resize(n + 1, 1);
        components = n;
        maxSize = 1;
    }
    int find(int i)
    {
        if (i != parents[i])
        {
            parents[i] = find(parents[i]);
        }
        return parents[i];
    }
    void unionB(int i, int j)
    {
        int root_i = find(i);
        int root_j = find(j);
        int size_i = size[root_i];
        int size_j = size[root_j];
        if (root_i == root_j)
        {
            return;
        }
        if (size_i < size_j)
        {
            parents[root_i] = root_j;
            size[root_j] += size[root_i];
            components--;
            maxSize = max(maxSize, size[root_j]);
        }
        else
        {
            parents[root_j] = root_i;
            size[root_i] += size[root_j];
            components--;
            maxSize = max(maxSize, size[root_i]);
        }
    }
};

int main()
{
    fast_io();
    ll n, m;
    cin >> n >> m;
    DSU D(n);
    for (int i = 0; i < m; i++)
    {
        ll a, b;
        cin >> a >> b;
        D.unionB(a, b);
        cout << D.components << " " << D.maxSize << endl;
    }
}