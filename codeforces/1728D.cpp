#include <bits/stdc++.h>
using namespace std;
 
int t, n, dr, i;
char s[2010];
 
int main()
{
    cin >> t;
    while (t--) {
        cin >> (s+1);
        n = strlen(s+1);
        for (i = 1; i <= n/2 && s[i] == s[n-i+1]; i++);
        dr = n-i+1;
        for (; i <= dr && s[i] == s[i+1]; i += 2);
        if (i > dr)
            cout << "Draw";
        else
            cout << "Alice";
        cout << '\n';
    }
    return 0;
}