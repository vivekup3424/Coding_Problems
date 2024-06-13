//memoized approach for unbounded knapsack
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
static int memo[MAX][MAX]; //memo[n+1][W+1]

int knapsack(int wt[],int val[],int W,int n)
{
    /*wt = weight array
    val = value array
    W = Total weight
    n = total no of items
    */
   if(W==0||n==0)return 0;
   else if(wt[n-1]<=W)
   {
    return memo[n][W]= max(val[n-1]+knapsack(wt,val,W-wt[n-1],n),knapsack(wt,val,W,n-1));
   }
   else if(wt[n-1]>W){
    return memo[n][W]=knapsack(wt,val,W,n-1);
   }
   
}
int main()
{
    cout<<knapsack(wt,val,10,10)<<"\n";
}