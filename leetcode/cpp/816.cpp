#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    void backtrack(string s, int n, int idx, string a, string b, vector<string> &ans)
    {
        if (idx == n)
        {
            ostringstream oss;
            oss << "(" << a << ", " << b << ")";
            ans.push_back(oss.str());
        }
    }
    vector<string> ambiguousCoordinates(string s)
    {
    }
};