// 151. Reverse words in a string

#include <bits/stdc++.h>
using namespace std;
// https://www.codingninjas.com/studio/problems/reverse-words-in-a-string_696444?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf
class Solution
{
public:
    // Trim leading, trailing and extra whitespace from string
    // Assuming only spaces for whitespace
    std::string trim1(const std::string &str)
    {

        std::string result;

        // Find first non-space char
        size_t start = str.find_first_not_of(' ');

        // Find end of string
        size_t end = str.find_last_not_of(' ') + 1;

        // Iterate through string
        bool prev_was_space = true;
        for (size_t i = start; i < end; i++)
        {

            char c = str[i];

            // Skip spaces
            if (c == ' ')
            {
                if (prev_was_space)
                {
                    continue;
                }
                prev_was_space = true;
            }
            else
            {
                prev_was_space = false;
            }

            // Add non-space char
            result += c;
        }

        return result;
    }
    std::string trim(const std::string &str)
    {

        std::string result;

        // Trim leading spaces
        size_t start = str.find_first_not_of(' ');
        if (start == std::string::npos)
        {
            return result; // string is all spaces
        }

        // Trim trailing spaces
        size_t end = str.find_last_not_of(' ') + 1;

        bool last_char_was_space = false;

        for (size_t i = start; i < end; i++)
        {
            char c = str[i];
            if (std::isspace(c))
            {
                if (!last_char_was_space)
                {
                    result += ' ';
                }
                last_char_was_space = true;
            }
            else
            {
                result += c;
                last_char_was_space = false;
            }
        }

        return result;
    }
    string reverseWords1(string s)
    { // Method 1:- Trim the sentence and then reverse, I think this one is easier
        string ans = trim(s);
        // reverse the whole sentence now
        reverse(ans.begin(), ans.end());
        // now reverse each word inside the sentence now
        int start = 0;
        for (int i = 0; i <= ans.size(); i++)
        {
            if (i == ans.size() || ans[i] == ' ')
            {
                reverse(&ans[start], &ans[i]);
                start = i + 1;
            }
        }
        return ans;
    }
};
int main()
{
}