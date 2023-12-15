#include <bits/stdc++.h>
using namespace std;
#define MAX 100
int max(int a,int b)
{
    if(a>=b)return a;
    else return b;
}
int length[8] = {1,2,3,4,5,6,7,8};
int price[8] = {1,5,8,9,10,17,17,20};
static int memo[MAX][MAX]; //memo[n+1][L+1], memo[i][j] = max price for ith items, and jth length
static int L = 8; //L = length of rod
//we have to get maximum price
//n = no of pieces

int max_rod(int length[],int price[],int L,int n)
{
    if(L==0||n==0)return 0;
    else if(length[n-1]>L)return memo[n][L]=max_rod(length,price,L,n-1);
    else if(length[n-1<=L]){
        return memo[n][L]=max(price[n-1]+max_rod(length,price,L-length[n-1],n),
    max_rod(length,price,L,n-1));
    }
}
int main()
{
    cout<<max_rod(length,price,8,8)<<"\n";
}