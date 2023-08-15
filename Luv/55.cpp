
#include <bits/stdc++.h>
using namespace std;
const int M = 10 ^ 9 + 7;
// a <= 10^9 , b <=10^9
int binary_exponentiation(int a, int b)
{
    // for a >=10^9
    a = a % M;
    int ans = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = ans * a;
        }
        a *= a;
        b >>= 1;
    }
    return ans;
}
int main()
{
    cout << binary_exponentiation(2, 10);
}