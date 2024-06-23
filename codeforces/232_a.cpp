
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int p = 0;
    while (n--)
    {
        string s;
        cin >> s;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '+')
            {
                p++;
                i++;
            }
            else if (s[i] == '-')
            {
                p--;
                i++;
            }
        }
    }
    cout << p << endl;
}