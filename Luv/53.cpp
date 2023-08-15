// GCD and LCM using EUCLID's Algorithm with Applications | CP Course | EP 53

#include <bits/stdc++.h>
int GCD(int a, int b) // using Euclid's algorithm
{
    if (b == 0)
        return a;
    return gcd(b, a % b)
}
using namespace std;

int main()
{
}