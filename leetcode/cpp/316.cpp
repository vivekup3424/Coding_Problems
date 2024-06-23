
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string removeDuplicateLetters(string s)
    {
        vector<bool> visited(26, false);
        vector<char> v;
        for (auto c : s)
        {
            if (visited[c - 'a'])
            {
                continue;
            }
            else
            {
                visited[c - 'a'] = true;
                v.push_back(c);
            }
        }
        sort(v.begin(), v.end());
        string result = "";
        for (auto c : v)
        {
            result += c;
        }
        return result;
    }
};
int main()
{
}