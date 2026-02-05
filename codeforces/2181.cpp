#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int w,h,d;
    cin>>w>>h>>d;
    int n;
    cin>>n;
    int gcd_w = __gcd(w,n);
    cout<<gcd_w-1<<" ";
    n /= gcd_w;
    int gcd_h = __gcd(h,n);
    cout<<gcd_h-1<<" ";
    n /= gcd_h;
    int gcd_d = __gcd(d,n);
    cout<<gcd_d-1<<endl;
    return 0;
}
