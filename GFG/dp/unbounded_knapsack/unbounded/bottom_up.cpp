//bottom_up approach for unbounded knapsack
#include <bits/stdc++.h>
using namespace std;
#define MAX 100
int max(int a,int b)
{
    if(a>=b)return a;
    else return b;
}
//recursive solution
int wt[10] = {1,2,3,4,5,6,7,8,9,10};
int val[10] = {1,2,3,4,5,6,7,8,9,10};
int memo[MAX][MAX]; //memo[n+1][W+1]

int knapsack(int wt[],int val[],int W,int n)
{
    /*wt = weight array
    val = value array
    W = Total weight
    n = total no of items
    */
   for (int i = 0; i < n+1; i++)
   {
        for (int j = 0; j < W+1; j++)
        {
            if(i==0||j==0)memo[i][j]=0;
            else if(wt[i-1]<=j) //j is currently capacity
            {
                memo[i][j] = max(val[i-1]+memo[i][j-wt[i-1]],memo[i-1][j]);
                //including the ith item, or not including it
                //choose the max between the two
            }
            
            //not including the items which are over-weight
            //wt[i-1]>W
            else memo[i][j] = memo[i-1][j];
        }
   }
   return memo[n][W];
}
int main()
{
    cout<<knapsack(wt,val,10,10)<<"\n";
}