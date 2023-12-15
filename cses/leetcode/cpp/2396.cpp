#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string convertNum(int num, int base)
    {
        string s;
        while (num)
        {
            s.push_back(num % base);
            num /= base;
        }
        return s;
    }
    bool isPalindrome(string s)
    {
        string temp = s;
        reverse(s.begin(), s.end());
        return s == temp;
    }
    bool isStrictlyPalindromic(int n)
    {
        for (int i = 2; i <= n - 2; i++)
        {
            string s = convertNum(n, i);
            if (!isPalindrome(s))
                return false;
        }
        return true;
    }
};
int main()
{
}