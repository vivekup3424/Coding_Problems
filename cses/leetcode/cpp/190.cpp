
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        int totalBits = 32;
        uint32_t ans = 0;
        while (totalBits)
        {
            ans = (ans << 1) | (n & 1);
            n >>= 1; // right-shift to process next bit
            totalBits--;
        }
        return ans;
    }
};
int main()
{
}