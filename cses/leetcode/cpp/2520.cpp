
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int countDigits(int num)
    {
        string s = to_string(num);
        int count = 0;
        for (auto c : s)
        {
            if (num % (c - '0') == 0)
                count++;
        }
        return count;
    }
};
class Solution2
{
public:
    int countDigits(int num)
    {
        int count = 0;
        int numcopy = num;
        while (numcopy)
        {
            int rem = numcopy % 10;
            if (num % rem == 0)
                count++;
            numcopy = numcopy / 10;
        }
        return count;
    }
};
int main()
{
}