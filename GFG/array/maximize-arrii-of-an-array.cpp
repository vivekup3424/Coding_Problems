#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int maximize(vector<int> v)
{
    sort(v.begin(), v.end());
    int sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sum += (i * v[i]) % MOD;
        sum %= MOD;
    }
    return sum;
}