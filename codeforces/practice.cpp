#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    int n = 101;
    int lcm = 1;
    //create an array LCM of size n,
    //such that LCM[i] = LCM of 1, 2, 3, 4, ... i
    
    vector<int> LCM(n+1,0);
    for(int i=1;i<=n;i++){
        lcm = (lcm*i)/__gcd(lcm,i);
        LCM[i] = lcm;
    }
    for(int i=1;i<=n;i++){
        cout<<LCM[i]<<" ";
    }
    return 0;
}
