#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int minimumChairs(string s)
    {
        stack<char> stk;
        int maxSize = 0;
        for (char c : s)
        {
            if (c == 'E')
            {
                stk.push('E');
            }
            else if (c == 'L' and stk.size() > 0)
            {
                stk.pop();
            }
            if (stk.size() > maxSize)
            {
                maxSize = stk.size();
            }
        }
        return maxSize;
    }
};