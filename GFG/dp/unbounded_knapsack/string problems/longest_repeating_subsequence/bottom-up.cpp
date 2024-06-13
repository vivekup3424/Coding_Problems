// Longest Repeating Subsequence

// Given a string, print the longest repeating subsequence such that the
// two subsequence don’t have same string character at same position,
// i.e., any i’th character in the two subsequences shouldn’t have
// the same index in the original string.

// Example:
// Input: str = "aab"
// Output: "a"
// The two subsequence are 'a'(first) and 'a'
//(second). Note that 'b' cannot be considered
// as part of subsequence as it would be at same
// index in both.

// Algorithm
// Step 1: Initialize the input string, which is to be checked.
//
// Step 2: Initialize the length of string to the variable.
//
// Step 3: Create a DP table using 2D matrix and set each element to 0.
//
// Step 4: Fill the table if  characters are same and indexes are different.
//
// Step 5: Return the values inside the table
//
// Step 6: Print the String.
#include <bits/stdc++.h>
using namespace std;

// returns the length of longest repeating subsequence
int LCRS(string x, int a)
{
    int t[a + 1][a + 1];
    memset(t, -1, (a + 1) * (a + 1));
    for (int i = 0; i < a + 1; i++)
    {
        for (int j = 0; j < a + 1; j++)
        {
            if (i == 0 or j == 0)
                t[i][j] = 0;
            else if (x[i - 1] == x[j - 1] and i != j)
                t[i][j] = t[i - 1][j - 1] + 1;
            else
            {
                t[i][j] = max(t[i - 1][j], t[i][j - 1]);
            }
        }
    }
    int result = t[a][a];
    cout << result << "\n";
    return result;
}

int main()
{
    string str1 = "aaa";
    LCRS(str1, str1.size());
    return 0;
}