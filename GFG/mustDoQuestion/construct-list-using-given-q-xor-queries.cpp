#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> constructList(int q, vector<vector<int>> &queries)
{
    // inserting the elements
    vector<int> v;
    v.push_back(0);
    vector<int> xorPref(q + 1, 0);
    for (auto query : queries)
    {
        if (query[0] == 0)
        {
            v.push_back(query[1]);
        }
        else if (query[0] == 1)
        {
            xorPref[0] = xorPref[0] ^ query[1];
            xorPref[v.size()] ^= query[1];
        }
    }
    // constructing the xorPref
    for (int i = 1; i < q + 1; i++)
    {
        xorPref[i] = xorPref[i] ^ xorPref[i - 1];
    }
    // xor all the elements of vector v
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = v[i] ^ xorPref[i];
    }
    sort(v.begin(), v.end());
    return v;
}