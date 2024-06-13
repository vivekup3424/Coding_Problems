#include <iostream>
#include <cstring>
using namespace std;
int CountMaxSubsetCoins(int coins[],int n,int Sum) //n = number of(types) coins
{
    int memo[n+1][Sum+1];
    memset(memo,-1,(n+1)*(Sum+1));
    if (memo[n][Sum]!=-1)return memo[n][Sum];
    
    if(Sum==0)return memo[n][Sum]=1;
    else if(n==0)return 0;
    else if(coins[n-1]>Sum) return memo[n][Sum] = CountMaxSubsetCoins(coins,Sum,n-1);
    else
    {
        //including the nth coin and not including the nth coin
        return memo[n][Sum] = (CountMaxSubsetCoins(coins,Sum-coins[n-1],n) + CountMaxSubsetCoins(coins,Sum,n-1));
    }
    //Time Complexity = O(2^Sum), Space Complexity = O(n)
}