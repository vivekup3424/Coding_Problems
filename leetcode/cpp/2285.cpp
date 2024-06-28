#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    long long maximumImportance(int n, vector<vector<int>> &roads)
    {
        // creating an hashmap for the degree
        long long cnt[50001] = {}, res = 0;
        for (auto &r : roads)
        {
            ++cnt[r[0]];
            ++cnt[r[1]];
        }
        sort(begin(cnt), begin(cnt) + n);
        for (int i = 0; i < n; ++i)
            res += cnt[i] * (i + 1);
        return res;
    }
};