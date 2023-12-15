
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxValue(int n, int index, int maxSum)
    {
        int c = maxSum / n;
        int diff = maxSum - (c * n);
        int r = (-1 + (int)sqrt(1 + 4 * diff)) / 2;
        return r - 1;
    }
};
int main()
{
}