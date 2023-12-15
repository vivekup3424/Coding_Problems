#include <bits/stdc++.h>
using namespace std;

int fact(int n)
{
    if(n==0 || n== 1)return 1;
    else return fact(n-1) * n;
    //This problem can't be reduced by DP, as there no scope of memoization
    //but we can reduce space complexity by following bottom-up approach
}
int fibo(int n)
{
    if(n==1)return 0;
    else if(n==2) return 1;
    else
    {
        return fibo(n-1)+fibo(n-2);
    }
    
}

int main()
{

}