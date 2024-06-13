/*Minimum number of deletions and insertions to transform one 
string into another*/

/*
Given two strings ‘str1’ and ‘str2’ of size m and n 
respectively. The task is to remove/delete and insert 
the minimum number of characters from/in str1 to 
transform it into str2. It could be possible that 
the same character needs to be removed/deleted from 
one point of str1 and inserted to some another point.
*/

/*
Solving using DP
Algorithm: 

    *str1 and str2 be the given strings.
    *m and n be their lengths respectively.
    *len be the length of the longest common 
    subsequence of str1 and str2
    *minimum number of deletions minDel = m – len 
    (as we only need to delete from str1 because 
    we are reducing it to str2)
    *minimum number of Insertions minInsert = n – len 
    (as we are inserting x in str1 , x is a number 
    of characters in str2 which are not taking part 
    in the string which is longest common subsequence )
*/
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
void print_minimum_deletion_and_insertion(string X, string Y)
{
    int n = X.size();
    int m = Y.size();
    int lcs = LCS(X,Y,n,m);
    cout<<"Minimum number of deletions = "<<(n-lcs)<<"\n";
    cout<<"Minimum number of insertions = "<<(m-lcs)<<"\n";
    return ;
}
// Driver Code
int main()
{
    string str1 = "heap";
    string str2 = "pea";
   
      // Function Call
    print_minimum_deletion_and_insertion(str1, str2);
    return 0;
}