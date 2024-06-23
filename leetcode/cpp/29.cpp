#include <bits/stdc++.h>
using namespace std;
// Method 1: Using brute-force
class Solutions1
{
public:
    int divide(int dividend, int divisor)
    {
        int q = 0;
        while (dividend >= divisor)
        {
            dividend -= divisor;
            q++;
        }
    }
};

// Method 2: Using bit manipulation

int main()
{
}