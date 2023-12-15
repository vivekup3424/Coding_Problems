
#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true)
    {
        string s;
        cin >> s;
        if (s.size() == 0)
            break;
        transform(s.begin(), s.end(), s.begin(), ::toupper);
    }
}