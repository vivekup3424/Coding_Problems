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
int length[8] = {1,2,3,4,5,6,7,8};
int price[8] = {1,5,8,9,10,17,17,20};
int memo[MAX][MAX]; //memo[n+1][W+1]

int max_rod(int length[],int price[],int L,int n)
{
    /*length = length of different pieces
    price = price array
    L = Total length
    n = total no of items
    */
   for (int i = 0; i < n+1; i++)
   {
        for (int j = 0; j < L+1; j++)
        {
            if(i==0||j==0)memo[i][j]=0;
            else if(length[i-1]<=j) //j is currently capacity
            {
                memo[i][j] = max(price[i-1]+memo[i][j-length[i-1]],memo[i-1][j]);
                //including the ith item, or not including it
                //choose the max between the two
            }
            
            //not including the items which are over-length
            //length[i-1]>L
            else memo[i][j] = memo[i-1][j];
        }
   }
   return memo[n][L];
}
int main()
{
    cout<<max_rod(length,price,8,8)<<"\n";
}