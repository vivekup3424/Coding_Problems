
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string simplifyPath(string path)
    {
        stack<char> stk;
        for (char c : path)
        {
            if (c == '/')
            {
                if (stk.empty() == false and stk.top() == '/')
                {
                    continue;
                }
                else
                {
                    stk.push('/');
                }
            }
            else if (c == '.')
            {
                if (stk.empty() == false and stk.top() == '.')
                {
                    while (stk.top() != '/')
                    {
                        stk.pop();
                    }
                }
            }
            else
            {
                stk.push(c);
            }
        }
        string s;
        while (!stk.empty())
        {
            s.push_back(stk.top());
            stk.pop();
        }
        reverse(s.begin(), s.end());
        int n = s.size();
        if (n > 1 and s[n - 1] == '/')
            s.pop_back();

        return s;
    }
};
int main()
{
}