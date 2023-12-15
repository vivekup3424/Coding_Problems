
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        vector<string> result;
        if (digits.empty())
            return result;
        vector<string> mapping = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    }
    void backtrack(string combination, string &digits, int index, vector<string> &mapping, vector<string> &result)
    {
        if (index == digits.length())
        {
            result.push_back(combination);
        }
        string letters = mapping[digits[index] - '0'];
        for (auto letter : letters)
        {
            backtrack(combination + letter, digits, index + 1, mapping, result);
        }
    }
};
int main()
{
}