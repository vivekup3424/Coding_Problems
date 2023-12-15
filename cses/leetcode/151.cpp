//

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string reverseWords(string s)
    {
        int length = s.size(),
            start = length - 1, end = length - 1;
        string ans;
        while (end >= 0)
        {
            if (s[end] == ' ')
            {
                ans += s.substr(end + 1, start - end + 1);
                while (s[end] == ' ')
                {
                    end--;
                }
                start = end;
            }
            end--;
        }
        return ans;
    }
};
int main()
{
    string ans = "  the sky is blue";
    Solution A = Solution();
    cout << A.reverseWords(ans) << endl;
}