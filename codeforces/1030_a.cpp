
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int r = 0;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        r |= t;
    }
    if (r == 1)
        cout << "HARD" << endl;
    else
        cout << "EASY" << endl;
    return 0;
}