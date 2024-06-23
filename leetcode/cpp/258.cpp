
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int addDigits(int num)
    {
        if (num / 10 == 0)
        {
            return num;
        }
        else
        {
            int n = 0;
            while (num > 0)
            {
                n += num % 10;
                num /= 10;
            }
            return addDigits(n);
        }
    }
};
int main()
{
    int n = 38;
    Solution A;
    A.addDigits(n);
}