
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int length = 0, maxLength = 0;
        stack<char> st;
        for (char c : s)
        {
            if (st.empty())
            {
                if (c == '(')
                {
                    st.push(c);
                }
                else
                {
                    st.push('-');
                    length = 0;
                }
            }
            else if (st.top() == '-')
            {
                if (c == '(')
                {
                    while (!st.empty())
                    {
                        st.pop();
                    }
                    st.push(c);
                }
                else
                {
                    continue;
                }
            }
            else
            {
                if (c == '(')
                    st.push(c);
                else
                {
                    st.pop();
                    length += 2;
                }
            }
            maxLength = max(length, maxLength);
        }
        return maxLength;
    }
};

// Below is the code given by chatgpt
class Solution1
{
public:
    int longestValidParentheses(string s)
    {
        int length = 0, maxLength = 0;
        stack<char> charStack;
        stack<int> lengthStack;

        for (char c : s)
        {
            if (c == '(')
            {
                charStack.push(c);
                lengthStack.push(length);
                length = 0;
            }
            else if (c == ')' && !charStack.empty() && charStack.top() == '(')
            {
                charStack.pop();
                length = lengthStack.top() + length + 2;
                lengthStack.pop();
                maxLength = max(maxLength, length);
            }
            else
            {
                // Reset length if a mismatched closing parenthesis is encountered.
                length = 0;
            }
        }

        return maxLength;
    }
};

int main()
{
    Solution A;
    string s = ")()())";
    int n = A.longestValidParentheses(s);
    cout << n << endl;
    return 0;
}