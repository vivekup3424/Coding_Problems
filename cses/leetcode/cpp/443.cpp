//

#include <bits/stdc++.h>
using namespace std;
class Solution
{
    // I have thought of this solution, uses only constant extra space
public:
    int compress(vector<char> &chars) //["a","a","b","b","c","c","c"]
    {
        int length = chars.size(); // 7
        int start = 0;
        for (int i = 0; i < length; i++)
        {
            int temp_length = 1;
            chars[start++] = chars[i];
            while (i + 1 < length and chars[i] == chars[i + 1]) // i = 0
            {
                temp_length++;
                i++;
            }
            if (temp_length > 1)
            {
                string t = to_string(temp_length);
                for (auto c : t)
                {
                    chars[start++] = c;
                }
            }
        }
        return start + 1;
    }
};
class Solution
{
    // I have thought of this solution, uses only constant extra space
public:
    int compress(vector<char> &chars) //["a","a","b","b","c","c","c"]
    {
        int length = chars.size(); // 7
        int start = 0;
        vector<char> ans;
        for (int i = 0; i < length; i++)
        {
            int temp_length = 1;
            ans.push_back(chars[i]);
            while (i + 1 < length and chars[i] == chars[i + 1]) // i = 0
            {
                temp_length++;
                i++;
            }
            if (temp_length > 1)
            {
                string t = to_string(temp_length);
                for (auto c : t)
                {
                    ans.push_back(c);
                }
            }
        }
        chars = ans;
        return ans.size();
    }
};
int main()
{
}