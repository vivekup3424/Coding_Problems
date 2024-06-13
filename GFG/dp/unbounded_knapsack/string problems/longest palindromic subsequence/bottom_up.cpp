#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int LCS(string X,string Y, int n,int m) //n=length of X, m=length of Y
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

//finds the length of longest common palindromic subsequence
int LPS(string X)
{
    int n = X.size();
    string Y; //Y is the reverse of X
    for (int i = n-1; i >=0; i--)
    {
        Y.push_back(X[i]);
    }
    int m = n;
    int lps = LCS(X,Y,n,m);
    return lps; //lps would the lcs of string and its inverted string
};
//Time complexity: O(n^2) and Space Complexity: O(n^2)
int main()
{
    string X = "agbcba";
    int lps = LPS(X);
    cout<<"LPS = "<<lps<<".\n";
    return 0;
}