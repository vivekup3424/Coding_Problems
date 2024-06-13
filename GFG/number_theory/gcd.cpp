// https://en.wikipedia.org/wiki/Euclidean_algorithm

#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
    // Time Complexity: O(log(min(a,b)) | Auxiliary Space: O(log(min(a,b))
}
int GCD(int a, int b)
{
    return __gcd(a, b);
    // time = O(logn), space = O(1)
}
// or you can use the built in gcd function
int main()
{
}