// 43. Multiply Strings
#include <bits/stdc++.h>
using namespace std;
class Solution1 // this is a failed solution as this is causing overflow
{               // hence this naive approach is not working
public:
    string multiply(string num1, string num2)
    {
        if (num1 == "0" || num2 == "0")
        {
            return "0";
        }
        int n1 = convert(num1);
        int n2 = convert(num2);
        int n = n1 * n2;
        return convert(n);
    }
    int convert(string s)
    {
        int n = s.length();
        int sum = 0;
        int counter = -1;
        for (int i = n - 1; i >= 0; i--)
        {
            counter++;
            sum += (s[i] - '0') * pow(10, counter);
        }
        return sum;
    }
    string convert(int n)
    {
        string s = "";
        while (n)
        {
            s += (n % 10) + '0';
            n /= 10;
        }
        reverse(s.begin(), s.end());
        return s;
    }
};
class Solution
{
public:
    string multiply(string num1, string num2)
    {
        string result = "";
    }
};
int main()
{
}