//1221. Split string in balanced strings

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int balancedStringSplit(string s) {
    int count = 0, ans = 0;
    for(int i = 0;i<s.size();i++)
    {
        if(s[i]=='R')count++;
        else if(s[i]=='L')count--;
        if(count==0)ans++;
    }    
    return ans;
    }
};
int main()
{
    string s;
    cin >> s;
    int count = 0;
    int ans = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'R')
        {
            count++;
        }
        else
        {
            count--;
        }
        if (count == 0)
        {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}