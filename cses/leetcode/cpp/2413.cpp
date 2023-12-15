// smallest even number

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int smallestEvenMultiple(int n)
    {
        if ((n & 1) == 0)
            return n;
        return n << 1;
    }
};
int main()
{
}