
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool isAlphaNum(char c)
    {
        if (('a' <= c and 'z' >= c) or ('A' <= c and 'Z' >= c) or ('0' <= c and '1' >= c))
            return true;
        return false;
    }
    char convertAlpha(char c)
    {
        if ('A' <= c)
            return c - 'A' + 'a';
        return c;
    }
    bool isPalindrome(string s)
    {
        int n = s.size();
        int i = 0, j = n - 1;
        while (i < j)
        {
            if (!isAlphaNum(s[i++]))
                continue;
            if (!isAlphaNum(s[j--]))
                continue;
            char c = convertAlpha(s[i++]), d = convertAlpha(s[j--]);
            if (c != d)
                return false;
        }
        return true;
    }
};
int main()
{
    Solution solution;
    std::string testString = "A man, a plan, a canal: Panama";
    bool isPalindrome = solution.isPalindrome(testString);

    std::cout << "Is the string a valid palindrome? " << (isPalindrome ? "Yes" : "No") << std::endl;

    return 0;
}