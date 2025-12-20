#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    int climbStairs(int n){
        if(n<=0)return n == 0;
        return climbStairs(n-1)+climbStairs(n-2);
    }
};
int main(){
    int number = 10;
    for(int i = 1; i<= number; i++){
        cout<<
    }
}