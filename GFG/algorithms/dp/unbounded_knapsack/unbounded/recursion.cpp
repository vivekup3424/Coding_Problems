/*Given a knapsack weight W and a set of n items 
with certain value val[i] and weight wt[i], we need 
to calculate the maximum amount that could make 
up this quantity exactly. */
/*or Knapsack with duplicate items*/
#include <bits/stdc++.h>
using namespace std;
int max(int a,int b)
{
    if(a>=b)return a;
    else return b;
}
//recursive solution
int wt[10] = {1,2,3,4,5,6,7,8,9,10};
int val[10] = {1,2,3,4,5,6,7,8,9,10};
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
    return max(val[n-1]+knapsack(wt,val,W-wt[n-1],n),knapsack(wt,val,W,n-1));
   }
   else if(wt[n-1]>W){
    return knapsack(wt,val,W,n-1);
   }
}
int main()
{
    cout<<knapsack(wt,val,10,10)<<"\n";
}