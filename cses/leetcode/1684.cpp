
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int countConsistentStrings(string allowed, vector<string> &words)
    {
        // Create a set to store the allowed characters
        unordered_set<char> allowedChars(allowed.begin(), allowed.end());
        int count = 0;
        // Iterate through each word in the vector
        for (string word : words)
        {
            bool consistent = true;
            // Iterate through each character in the word
            for (char c : word)
            {
                // If the character is not in the allowed set, mark the word as inconsistent
                if (allowedChars.find(c) == allowedChars.end())
                {
                    consistent = false;
                    break;
                }
            }
            // If the word is consistent, increment the count
            if (consistent)
            {
                count++;
            }
        }
        return count;
    }
};
int main()
{
    Solution s;
    string allowed = "ab";
    vector<string> words = {"ad", "bd", "aaab", "baa", "badab"};
    cout << s.countConsistentStrings(allowed, words) << endl;
    return 0;
}