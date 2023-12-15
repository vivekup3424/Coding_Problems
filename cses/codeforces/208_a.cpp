#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int flag = 0;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'W' && s[i + 1] == 'U' && s[i + 2] == 'B')
        {
            if (flag == 0)
                cout << " ";
            i += 2;
            flag = 1;
        }
        else
        {
            flag = 0;
            cout << s[i];
        }
    }
    return 0;
}