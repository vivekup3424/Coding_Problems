#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int LCS(string X,string Y, int n,int m) //n=length of X, m=length of Y
{
    int t[n+1][m+1];
    memset(t,-1,sizeof(t));
    if(n==0||m==0)return t[n][m]=0;
    else if(X[n-1]==Y[m-1])return t[n][m]=1+LCS(X,Y,n-1,m-1);
    else if(X[n-1]!=Y[m-1])return t[n][m]=max(LCS(X,Y,n,m-1),LCS(X,Y,n-1,m));
};
int main()
{

}