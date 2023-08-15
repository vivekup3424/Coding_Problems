/*Given an array of n integers, your task is to process q queries of the form:
what is the minimum value in range [a,b]?*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
// Method 1: Sparse Table
// Time Complexity: O(nlogn) for preprocessing and O(1) for each query
// Space Complexity: O(nlogn)

vector<vector<lli>> lookup; // lookup[i][j] stores the minimum value in range [i, i+2^j-1]
void buildSparseTable(vector<lli> v)
{
    int n = v.size();
    int logn = (int)log2(n) + 1;
    lookup.resize(n, vector<lli>(logn));
    // Initializing lookup[][] for the intervals with length 1
    for (auto i = 0; i < n; i++)
    {
        lookup[i][0] = v[i];
    }
    // using the bottom-up approach to fill the look up table
    for (auto j = 1; (1 << j) <= n; j++)
    {
        for (auto i = 0; (i + (1 << j) - 1) < n; i++)
        {
            lookup[i][j] = min(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r)
{
    int j = (int)log2(r - l + 1); // highest power of 2, +1 because of we are including both l and r elements
    return min(lookup[l][j], lookup[r - (1 << j) + 1][j]);
}
int main()
{
    fast_io();
    int n, q;
    cin >> n >> q;
    vector<lli> v(n);
    for (auto &i : v)
        cin >> i;
    buildSparseTable(v);
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--; // 0-based indexing
        r--;
        cout << query(l, r) << "\n";
    }
    return 0;
}

// Method 2: Segment Tree
