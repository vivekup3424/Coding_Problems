// Minimum number of deletions and insertions to transform one string into another
// Given two strings ‘str1’ and ‘str2’ of size m and n respectively.
// The task is to remove/delete and insert minimum number of characters
// from /in str1 so as to transform it into str2.
// It could be possible that the same character needs to be removed/deleted from one point of str1 and inserted to some another point.
// Example:
// Input : str1 = "geeksforgeeks", str2 = "geeks"
// Output : Minimum Deletion = 8
//          Minimum Insertion = 0

// Solution
// 1. First find the LCS of the pair of strings
#include <bits/stdc++.h>
using namespace std;
int LCS(string X, string Y, int n, int m) // n=length of X, m=length of Y
{
    if (n == 0 || m == 0)
        return 0;
    else if (X[n - 1] == Y[m - 1])
        return 1 + LCS(X, Y, n - 1, m - 1);
    else if (X[n - 1] != Y[m - 1])
        return max(LCS(X, Y, n, m - 1), LCS(X, Y, n - 1, m));
};

int min_insertion_deletion(string x, string y, int a, int b) // a = length of x
{
    // converting x->y
    // if(a>b)=> there should be deletions more than insertion
    // likewise if(a<b) there should be insertions more than deletion
    int lcs = LCS(x, y, a, b);
    int A = a - lcs;
    int B = b - lcs;
    // A deletions and B insertions
    int total = A + B;
    cout << A << " deletetions and " << B << " deletions\n";
    cout << total << "\n";
    return total;
}

int main()
{
    string str1 = "geeksforgeeks", str2 = "geeks";
    int a = str1.size(), b = str2.size();
    int minimum_insertion_deletion = min_insertion_deletion(str1, str2, a, b);
    return 0;
}