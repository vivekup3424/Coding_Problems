#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
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
        std::cout << "NO SOLUTION" << endl;
        return 0;
    }
    for (auto it : mp)
    {
        char element = it.first;
        if (mp[element] % 2 == 1)
        {
            ans[n / 2] = element;
            mp[element]--;
        }
        for (int f = 0; f < mp[element] / 2; f++)
        {
            ans[i++] = element;
            ans[j--] = element;
        }
    }
    std::cout << ans << endl;
    return 0;
}
