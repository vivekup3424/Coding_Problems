#include <bits/stdc++.h>
using namespace std;
#define MAX 1000
int fibonacci(int n) //return nth term //recursion
{
    if(n==1||n==2)
    {
        return 1;
    }
    else
    {
        return fibonacci(n-1)+fibonacci(n-2);
    }
}; 
static int memo[MAX];
int fibonacci_memo(int n)
{
    if(memo[n-1]!=0)return memo[n];
    else
    {
        memo[0] = 1,memo[1] = 1;
        return memo[n-1] = fibonacci_memo(n-1)+fibonacci_memo(n-2);
    }
}
int main()
{
for (int i = 0; i < 100; i++)
{
    cout<<fibonacci_memo(i)<<" ";
}
cout<<"\n";
return  0;
}