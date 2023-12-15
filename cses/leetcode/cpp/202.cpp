
#include <bits/stdc++.h>
using namespace std;
int sumOfSquares(int n)
{
    int result = 0;
    while (n > 0)
    {
        int t = n % 10;
        result += (t * t);
        n = n / 10;
    }
    return result;
}
class Solution
{
public:
    bool isHappy(int n)
    {
        unordered_set<int> s;
        s.insert(n);
        while (true)
        {
            int temp = sumOfSquares(n);
            if (temp == 1)
                return true;
            else if (s.count(temp))
                return false;
            s.insert(temp);
            n = temp;
        }
        return true;
    }
};
int main()
{
    Solution A;
    int n = 4;
    A.isHappy(n);
}