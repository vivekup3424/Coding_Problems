
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    char findTheDifference(string s, string t)
    {
        int ans = 0;
        for (auto c : s)
        {
            ans = int(c) ^ ans;
        }
        for (auto c : t)
        {
            ans = int(c) ^ ans;
        }
        return char(ans);
    }
};
int main()
{
}