#include <bits/stdc++.h>
using namespace std;

/**
 *Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', 
 determine if the input string is valid.

An input string is valid if:

    - Open brackets must be closed by the same type of 
    brackets.
    - Open brackets must be closed in the correct order.
    - Every close bracket has a corresponding open 
    bracket of the same typ
*/

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> stk;
        for (const char &c : s)
        {
            if (c == '(' or c == '{' or c == '[')
            {
                stk.push(c);
            }
            else if (c == ']')
            {
                if (stk.empty() or stk.top() != '[')
                    return false;
                else
                    stk.pop();
            }
            else if (c == '}')
            {
                if (stk.empty() or stk.top() != '{')
                    return false;
                else
                    stk.pop();
            }
            else if (c == ')')
            {
                if (stk.empty() or stk.top() != '(')
                    return false;
                else
                    stk.pop();
            }
        }
        if (!stk.empty())
            return false;
        return true;
    }
};
