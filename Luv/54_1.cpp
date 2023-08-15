// Bunary Exponentiation: Recursive Method | CP Course | EP 54.1

// why we can't use inbuilt power function
//  Reason=> precision error

#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int binExpRec(int a, int b)
{
    long res = binExpRec(a, b / 2);
    if (b == 0)
        return 1;
    if (b & 1)
    {
        return a * res * res;
    }
    else
    {
        return res * res;
    }
}
// Time complexity =
int main()
{
    double d = 1e24;
    cout << fixed << setprecision(30) << d;
    int a = 2, b = 13;
    // O(n) answer, using simple interation
    int ans = 1;
    for (int i = 0; i < b; i++)
    {
        ans *= a;
        // ans %=M;
    }
    cout << ans << "\n";

    // using binary exponentiation in O(logn) time
}
