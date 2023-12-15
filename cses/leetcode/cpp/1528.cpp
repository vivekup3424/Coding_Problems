
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string restoreString(string s, vector<int> &indices)
    {
        int n = indices.size();
        string answer(n, '-'); // placeholder string/ auxilliary string
        for (int i = 0; i < n; i++)
        {
            answer[indices[i]] = s[i];
        }
        string answer;
    }
};
int main()
{
}