
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int xorOperation(int n, int start)
    {
        int result = start;

        for (int i = 1; i < n; i++)
        {
            int num = start + 2 * i;
            result ^= num;
        }

        return result;
    }
};
int main()
{
    
}