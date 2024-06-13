#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class DSU
{
private:
    int vertices;
    vector<int> parents;

public:
    DSU(int n)
    {
        vertices = n;
        parents.resize(n);
        for (int i = 0; i < n; i++)
        {
            parents[i] = i;
        }
    }
    int find(int i)
    {
        if (parents[i] != i)
        {
            parents[i] = find(parents[i]); // path-compress
        }
        return parents[i];
    }
    void unionB(int i, int j)
    {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i == root_j)
        {
            return;
        }
        else if (root_i < root_j)
        {
            parents[j] = root_i;
        }
        else
        {
            parents[i] = root_j;
        }
    }
};

int main()
{
    ll N, Q;
    cin >> N >> Q;
    DSU d(N);
    for (int i = 0; i < Q; i++)
    {
        /* code */
        ll t, a, b;
        cin >> t >> a >> b;
        if (t == 0)
        {
            d.unionB(a, b);
        }
        else if (t == 1)
        {
            cout << int(d.find(a) == d.find(b)) << endl;
        }
    }
}