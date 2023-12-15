
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    const unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u',
                                        'A', 'E', 'I', 'O', 'U'};
    string reverseVowels(string s)
    {
        int l = 0, r = s.size() - 1;
        while (l < r)
        {
            if (!isVowel(s[l]))
                l++;
            else if (!isVowel(s[r]))
                r--;
            else
            {
                swap(s[l], s[r]);
                l++;
                r--;
            }
        }
        return s;
    }
    bool isVowel(char c)
    {
        if (vowels.find(c) != vowels.end())
            return true;
        return false;
    }
};
int main()
{
}