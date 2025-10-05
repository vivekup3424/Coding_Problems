#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        int longestDots = 0, currentLength = 0;
        for (int i = 0; i < n; i++)
        {
            if(s[i]=='.'){
                currentLength++;
                longestDots = max(longestDots,currentLength);
            }else if(s[i]=='#'){
                currentLength = 0;
            }
        }
        int answer = 0;
        if(longestDots>=3){
            answer = 2;
        }else{
            for(int i = 0;i < n; i++){
                if(s[i]=='.'){
                    answer++;
                }
            }
        }
        cout<<answer<<endl;
    }
}