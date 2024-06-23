
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    int flip = 0;
    for (int i = 1; i < n; i++)
    {
        if (s[i] != s[i - 1])
            flip++;
    }
    if (flip & 1)
    {
        cout << "No" << endl;
    }
    else
    {
        cout << "Yes" << endl;
    }
    return 0;
}