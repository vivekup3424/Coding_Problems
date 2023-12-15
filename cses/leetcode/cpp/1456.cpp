
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxVowels(string s, int k)
    {
        const set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int maxValue = 0, currentValue = 0;

        // Initialize currentValue for the first window
        for (int i = 0; i < k; i++)
        {
            if (vowels.count(s[i]))
            {
                currentValue++;
            }
        }
        maxValue = currentValue;

        // Slide the window and update currentValue
        for (int i = k; i < s.size(); i++)
        {
            if (vowels.count(s[i - k])) // Remove the leftmost character from the window
                currentValue--;
            if (vowels.count(s[i])) // Add the rightmost character to the window
                currentValue++;
            maxValue = max(maxValue, currentValue);
        }

        return maxValue;
    }
};

int main()
{
}