#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/**
 *Farmer John has received an order for exactly M units of milk (1≤M≤1,000) that he needs to fill right away. Unfortunately, his fancy milking machine has just become broken, and all he has are three milk pails of integer sizes X, Y, and M (1≤X<Y<M). All three pails are initially empty. Using these three pails, he can perform any number of the following two types of operations:

- He can fill the smallest pail (of size X
) completely to the top with X units of milk and pour it into the size-M pail, as long as this will not cause the size-M

pail to overflow.

- He can fill the medium-sized pail (of size Y
) completely to the top with Y units of milk and pour it into the size-M pail, as long as this will not cause the size-M

pail to overflow.

Although FJ realizes he may not be able to completely fill the size-M
pail, please help him determine the maximum amount of milk he can possibly add to this pail.
 */
int main(int argc, char const *argv[])
{
    int x, y, m;
    cin >> x >> y >> m;
    if (x > y)
    {
        swap(x, y);
    }
    int maxi = m / x;
    int ans = 0;
    for (int i = 0; i <= maxi; i++)
    {
        int temp = x * i;
        int temp2 = ((m - temp) / y) * y;
        ans = max(ans, temp + temp2);
    }
    cout << ans << endl;
    return 0;
}
