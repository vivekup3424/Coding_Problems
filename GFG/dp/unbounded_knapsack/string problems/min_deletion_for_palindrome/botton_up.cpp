/*Minimum number of deletion in a string to make it
Palindrome*/

#include <bits/stdc++.h>
using namespace std;

// return length(LCS); n,m: length of X and Y respectively
int LCS(string X, string Y, int n, int m)
{
    int t[n + 1][m + 1];
    memset(t, -1, sizeof(t));
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < m + 1; j++)
        {
            if (i == 0 || j == 0)
                t[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                t[i][j] = 1 + t[i - 1][j - 1];
            else if (X[i - 1] != Y[j - 1])
                t[i][j] = max(t[i - 1][j], t[i][j - 1]);
        }
    }
    return t[n][m]; // Length of LCS
};

/// return Minimum number of deletion in a string to make it Palindrome
void minimum_deletion_palindrome(string X)
{
    int n = X.size();
    string Y; // Y is the reverse of X
    for (int i = n - 1; i >= 0; i--)
    {
        Y.push_back(X[i]);
    }
    int m = n;
    int lps = LCS(X, Y, n, m);
    cout << "Minimum number of deletions = " << (n - lps) << "\n";
    return;
}
// Time complexity: O(n^2) and Space Complexity: O(n^2)
int main()
{
    string X = "agbcba";
    minimum_deletion_palindrome(X);
    // int lps = LPS(X);
    // cout<<"LPS = "<<lps<<".\n";
    return 0;
}