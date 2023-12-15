//The naive solution for this problem is 
//to generate all subsequences of both given 
//sequences and find the longest matching subsequence. 
//This solution is exponential in term of time complexity.
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int LCS(string X,string Y, int n,int m) //n=length of X, m=length of Y
{
    if(n==0||m==0)return 0;
    else if(X[n-1]==Y[m-1])return 1+LCS(X,Y,n-1,m-1);
    else if(X[n-1]!=Y[m-1])return max(LCS(X,Y,n,m-1),LCS(X,Y,n-1,m));
};
int main()
{

}