#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
    int clumsy(int n){
        if(n<=2){
            return n;
        }
        else if(n==3){
            return 3 * clumsy(2);
        }else{
            return (n+1)-clumsy(n);
        }
    }
};
