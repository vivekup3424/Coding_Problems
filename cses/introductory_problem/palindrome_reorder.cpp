#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    freopen("input.txt", "r", stdin);
    string s;
    cin >> s;
    map<char, int> mp;
    for (char c : s)
    {
        mp[c]++;
    }
    int n = s.length();
    string ans = s;
    int i = 0, j = n - 1;
    // count the number of odd frequency element
    int oddCount = 0;
    for (auto it : mp)
    {
        if (it.second % 2 == 1)
        {
            oddCount++;
        }
    }
    if (oddCount > 1)
    {
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    for (auto it : mp)
    {
        char element = it.first;
        if (mp[element] == 1)
        {
            ans[n / 2] = element;
            continue;
        }
        else
        {
            for (int f = 0; f < mp[element] / 2; f++)
            {
                ans[i++] = element;
                ans[j--] = element;
            }
        }
    }
    cout << "Outputing the map:'\n";
    for (auto it : mp)
    {
        cout << it.first << " " << it.second << endl;
    }
    // cout << ans << endl;
    return 0;
}
