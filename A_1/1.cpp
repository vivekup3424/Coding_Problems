#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
int main()
{
    lli n;
    cin >> n;
    while (1)
    {
        cout << n << " ";
        if (n == 1)
            break;
        else if (n % 2 == 1)
            n = 3 * n + 1;
        else
            n = n >> 1;
    }
}