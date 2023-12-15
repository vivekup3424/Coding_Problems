// Your task is to count for k=1,2,…,n
// the number of ways two knights can be
// placed on a k×k chessboard so that they
// do not attack each other.
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
llu num_of_positions(llu n)
{
    return (pow(n, 2) * (pow(n, 2) - 1)) / 2 - 4 * (n - 2) * (n - 1);
}

int main()
{
    llu k;
    cin >> k;
    for (llu i = 1; i <= k; i++)
    {
        cout << num_of_positions(i) << "\n";
    }
    return 0;
}
