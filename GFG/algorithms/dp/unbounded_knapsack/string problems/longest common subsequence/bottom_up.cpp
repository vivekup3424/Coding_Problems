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
int main()
{

}