#include <bits/stdc++.h>
using namespace std;

int mod = 1000000007;
//Function to find the nth catalan number.
int findCatalan(int n) 
{
    int a = 1;
    cout<<"0 = "<<a<<endl;
    for(int i = 1; i < n; i++){
        int t = (((a * 2*(2*i -1))%mod)/(i+1))%mod;
        cout<<i<<" = "<<t<<endl;
        a = t;
    }
    return a;
}
int main(){
    findCatalan(100);
}