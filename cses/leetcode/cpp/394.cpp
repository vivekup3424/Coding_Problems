
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string decodeString(string s)
    {
        stack<char> stk;
        for (char c : s)
        {
            if (c != ']')
            {
                stk.push(c);
            }
            else
            {
                // we encounter ]
                string temp;
                int n;
                while (stk.top() != '[')
                {
                    temp.push_back(stk.top());
                    stk.pop();
                }
                stk.pop();
                string number;
                while (stk.empty() or isdigit(stk.top()))
                {
                    number.push_back(stk.top());
                    stk.pop();
                }
                reverse(number.begin(), number.end());
                n = stoi(number);
                reverse(temp.begin(), temp.end());
                while (n--)
                {
                    for (char c : temp)
                    {
                        stk.push(c);
                    }
                }
            }
        }
        string ans;
        while (!stk.empty())
        {
            ans.push_back(stk.top());
            stk.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
int main()
{
}