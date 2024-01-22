#include <bits/stdc++.h>
using namespace std;
//recursive
class Solution {
public:
    int numOfWays(string s, int i){
        int n = s.size();
        if(i>=n)return 1;
        else{
            if(s[i]=='0')return 0;
            else if( i+1 < n and (s[i]=='1' || (s[i]=='2' and '0'<=s[i+1] and s[i+1]<='6')))
                return numOfWays(s,i+1) + numOfWays(s,i+2);
            else return numOfWays(s,i+1);
        }
    }
    int numDecodings(string s) {
        return s.empty()? 0 : numOfWays(s,0);
    }
};

//memoizationS
class Solution {
public:
    int numOfWays(string s, int i,vector<int> &memo){
        int n = s.size();
        if(memo[i]!=-1)return memo[i];
        if(i==n)return memo[i] = 1; //reached the last
        else{
            if(s[i]=='0')return memo[i] = 0;
            else if( i+1 < n and (s[i]=='1' || (s[i]=='2' and '0'<=s[i+1] and s[i+1]<='6')))
                return memo[i] = (numOfWays(s,i+1, memo) + numOfWays(s,i+2, memo));
            else return memo[i] = numOfWays(s,i+1, memo);
        }
    }
    int numDecodings(string s) {
        int n = s.size();
        vector<int> memo(n+1, -1);
        return s.empty()? 0 : numOfWays(s,0, memo);
    }
};

//dp
class Solution {
public:
    int numDecodings(string s) {
       int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n+1);
        dp[n] = 1;
        for(int i=n-1;i>=0;i--) {
            if(s[i]=='0') dp[i]=0;
            else {
                dp[i] = dp[i+1];
                if(i<n-1 && (s[i]=='1'||s[i]=='2'&&s[i+1]<'7')) dp[i]+=dp[i+2];
            }
        }
        return s.empty()? 0 : dp[0];   
    }
    }
};
int main(){
string s = "27";
Solution *A = new Solution();
int n = A->numDecodings(s);
}