#include <bits/stdc++.h>
using namespace std;
int recurse(vector<int> &v, int i, int j, bool turn, int count)
{
    if (i > j and turn)
    {
        return count;
    }
    if (i > j and !turn)
    {
        return 0;
    }
    if (turn)
    {
        return max(recurse(v, i + 1, j, !turn, count + v[i]), recurse(v, i, j - 1, !turn, count + v[j]));
    }
    else
    {
        return min(recurse(v, i + 1, j, !turn, count), recurse(v, i, j - 1, !turn, count));
    }
}
int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &i : v)
        cin >> i;
    vector<vector<int>> dp(n, vector<int>(2, 0));
    return 0;
}
