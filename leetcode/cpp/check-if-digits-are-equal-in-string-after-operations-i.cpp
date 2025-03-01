#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int charToNumber(char c)
    {
        return c - '0';
    }
    char numToChar(int i)
    {
        return i + '0';
    }
    string shortify(string s)
    {
        if (s.size() == 2)
        {
            return s;
        }
        string temp = "";
        for (int i = 0; i < s.size() - 1; i++)
        {
            int new_num = charToNumber(s[i]) + charToNumber(s[i + 1]);
            char new_char = numToChar(new_num % 10);
            temp.push_back(new_char);
        }
        return temp;
    }
    bool hasSameDigits(string s)
    {
        if (s.size() < 2)
        {
            return false;
        }
        while (s.size() > 2)
        {
            s = shortify(s);
            auto currentChar = s.front();
            for (auto c : s)
            {
                if (c != currentChar)
                {
                    return false;
                }
            }
        }
        return true;
    }
};
int main()
{
    cout << "Enter the number of strings :- \n";
    int n;
    cin >> n;
    while (n--)
    {
        cout << "Enter the string:-\n";
        string s;
        auto A = new Solution();
        cin >> s;
        cout << A->hasSameDigits(s) << endl;
    }
}