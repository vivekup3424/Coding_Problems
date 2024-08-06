#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int isValid(string str)
    {
        vector<string> numbers;
        string temp = "";
        for (char c : str)
        {
            if (c == '.')
            {
                numbers.push_back(temp);
                temp = "";
            }
            else
            {
                temp.push_back(c);
            }
        }
        numbers.push_back(temp);
        if (numbers.size() != 4)
        {
            return false;
        }
        bool sanityCheck = true;
        set<string> st;
        for (int i = 0; i <= 255; i++)
        {
            st.insert(to_string(i));
        }
        for (string num : numbers)
        {

            if (!st.count(num))
            {
                sanityCheck = false;
                break;
            }
        }
        return sanityCheck;
    }
};