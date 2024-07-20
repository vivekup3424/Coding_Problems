#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int q;
    cin>>q;
    while (q--)
    {
        int n;
        cin>>n;
        string s,t;
        cin>>s>>t;
        bool dp[n+1];
        memset(dp,n+1,0);
        for (int i = 0; i <= n; i++)
        {
            if(i==0){
                dp[i] = true;
            }
            else{
                for(int j = 0; j < n; j++){
                    if(s[i]==s[i+j])
                }   
            }
        }
    }    
    return 0;
}
