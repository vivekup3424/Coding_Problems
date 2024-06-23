
#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    string s = to_string(n);
    string p;
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if (c > '4' and !(i == 0 and c == '9'))
        {
            c = '9' - c + '0';
        }
        p.push_back(c);
    }
    cout << p << endl;
}