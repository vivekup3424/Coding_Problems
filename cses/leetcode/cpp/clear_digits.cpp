#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    string clearDigits(string s)
    {
        stack<char> stk;
        for (char c : s)
        {
            if (c >= '0' and c <= '9')
            {
                if (stk.size() > 0)
                {
                    stk.pop();
                }
            }
            else
            {
                stk.push(c);
            }
        }
        string temp;
        while (stk.size() > 0)
        {
            temp.push_back(stk.top());
            stk.pop();
        }
        reverse(temp.begin(), temp.end());
        return temp;
    }
};