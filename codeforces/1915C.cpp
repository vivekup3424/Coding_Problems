#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
typedef std::vector<int> vi; 

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
bool isPerfectSquare(int x)
{
    // Find floating point value of
    // square root of x.
    if (x >= 0) {
 
        int sr = sqrt(x);
         
        // if product of square root 
        //is equal, then
        // return T/F
        return (sr * sr == x);
    }
    // else return false if n<0
    return false;
}
 

int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin>>n;
        llu sum = 0;
        for(int i  = 0 ; i < n;i++)
        {
            llu temp;
            cin >> temp;
            sum += temp;
        }
        //cout<<"Sum = "<<sum<<endl;
        if(isPerfectSquare(sum))cout<<"YES\n";
        else cout<<"NO\n";
        
    }
}
