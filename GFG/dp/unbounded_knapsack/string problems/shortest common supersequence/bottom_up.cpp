//SSS
/*Given two strings str1 and str2, the task is to find the length 
of the shortest string that has both str1 and str2 as subsequences.*/
/*
1) Find Longest Common Subsequence (lcs) of two given strings. 
For example, lcs of “geek” and “eke” is “ek”. 
2) Insert non-lcs characters (in their original order in strings)
to the lcs found above, and return the result. So “ek” becomes “geeke” 
which is shortest common supersequence.*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//return length(LCS); n,m: length of X and Y respectively
int LCS(string X,string Y, int n,int m)
{
    int t[n+1][m+1];
    memset(t,-1,sizeof(t));
    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < m+1; j++)
    {
        if(i==0||j==0)t[i][j]=0;
        else if(X[i-1]==Y[j-1])t[i][j]=1+t[i-1][j-1];
        else if(X[i-1]!=Y[j-1])t[i][j] = max(t[i-1][j],t[i][j-1]);
    }
    }
    return t[n][m]; //Length of LCS
};

//returns length of shortest common supersequence
int SSS(string X, string Y)
{
    int n = X.size();
    int m = Y.size();
    int lcs = LCS(X,Y,n,m);
    // Result is sum of input string
    // lengths - length of lcs
    return (m+n-lcs);
    //Time Complexity: O(m*n).
}
// Driver code
int main()
{
    string X = "AGGTAB";
    string Y = "GXTXAYB";
 
    cout << "Length of the shortest supersequence is "
         << SSS(X, Y) << endl;
 
    return 0;
}