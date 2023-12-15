// 1071. Greatest Common Divisor of Strings

#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    string gcdOfStrings(string str1, string str2)
    {
        int l1 = str1.length(), l2 = str2.length();
        string base;
        if (l1 < l2)
        {
            base = str1;
        }
        else
            base = str2;
        while (!(isDivisible(str1, base) and isDivisible(str2, base) and (base.length() > 0)))
        {
            base.pop_back();
        }
        return base;
    }
    bool isDivisible(string dividend, string divisor)
    {
        int n1 = dividend.length(), n2 = divisor.length();
        if (n1 % n2 == 0)
        {
            int p = n1 / n2;
            string result = "";
            while (p--)
            {
                result += divisor;
            }
            if (result == dividend)
                return true;
        }
        return false;
    }
    // Time-complexity = O(min(m,n)*(m+n))
};
class Solution2
{
public:
    string gcdOfStrings(string s1, string s2)
    {
        if (!checkGCD(s1, s2))
            return "";
        int a = s1.length(), b = s2.length();
        int n = gcd(a, b);
        string s = s1.substr(0, n);
        return s;
    }
    bool checkGCD(string s1, string s2)
    {
        string r = s1 + s2;
        string s = s2 + s1;
        return r == s;
    }
    int gcd(int a, int b)
    {
        if (a == 0)
            return b;
        else
            return gcd(b % a, a);
    }
};
class Solution
{
public:
    string gcdOfStrings(string s1, string s2)
    {
        if (!checkGCD(s1, s2))
            return "";
        int a = s1.length(), b = s2.length();
        int n = gcd(a, b);
        string s = s1.substr(0, n);
        return s;
    }
    bool checkGCD(string s1, string s2)
    {
        return (s1 + s2) == (s2 + s1);
    }
};
int main()
{

    Solution *A = new Solution();
    cout << A->checkGCD("ABABAB", "AB");
}