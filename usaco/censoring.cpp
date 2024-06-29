#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
int main(int argc, char const *argv[])
{
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);
    string s;
    string t;
    cin >> s >> t;
    cout << Solution().removeOccurrences(s, t) << endl;
    return 0;
}
