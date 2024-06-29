#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 1.Simulatting the process
/*
iterate through the input string s and check if the substring part is present. If it is present, remove it from s and repeat the process until all occurrences of part are removed.
*/
string removeOccurrencesSimulation(string s, string t)
{
    while (s.size() > 0 && s.find(t) < s.size())
    {
        s.erase(s.find(t), t.size());
    }
}

// using stack to process it in O(n*m) time
class Solution
{
public:
    string removeOccurrences(string s, string part)
    {
        stack<char> st;
        for (char c : s)
        {
            st.push(c);
            if (st.size() >= part.length() && st.top() == part.back())
            {
                string temp = "";
                for (int i = 0; i < part.length(); i++)
                {
                    temp += st.top();
                    st.pop();
                }
                reverse(temp.begin(), temp.end());
                if (temp != part)
                {
                    for (char c : temp)
                    {
                        st.push(c);
                    }
                }
            }
        }
        string ans = "";
        while (!st.empty())
        {
            ans += st.top();
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};