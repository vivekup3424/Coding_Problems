/*The naive solution for this problem is to generate all 
subsequences of the given sequence and find the longest 
palindromic subsequence. This solution is exponential in 
terms of time complexity.*/
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

//returns the longest common subsequence of two strings
int LCS(string X,string Y, int n,int m) //n=length of X, m=length of Y
{
    if(n==0||m==0)return 0;
    else if(X[n-1]==Y[m-1])return 1+LCS(X,Y,n-1,m-1);
    else if(X[n-1]!=Y[m-1])return max(LCS(X,Y,n,m-1),LCS(X,Y,n-1,m));
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
int main()
{
    string X = "agbcba";
    int lps = LPS(X);
    cout<<"LPS = "<<lps<<".\n";
    return 0;
}