#include <bits/stdc++.h>
using namespace std;

class Solution{
private:
    bool isPalindrome(string &str){
        int n = str.length();
        int l = 0, r = n-1;
        while(l<r){
            if(str[l++]!=str[r--]){
                return false;
            }
        }
        return true;
    }
public:
    string longestPalindrome(string &s){
        int n = s.length();
        int maxLen = 1;
        string maxString = s.substr(0,1);
        for(int i = 0; i < n; i++){
            //finding for the odd length string
            int l = i, r = i;
            while (l >=0 and r < n and s[l]==s[r]) {
                if(maxLen < r - l +1){
                    maxLen = r - l + 1;
                    maxString = s.substr(l,maxLen);
                }
                l--;
                r++;
            }
            //finding for the even length string
            l = i, r = i+1;
            while (l >=0 and r < n and s[l]==s[r]) {
                if(maxLen < r - l +1){
                    maxLen = r - l + 1;
                    maxString = s.substr(l,maxLen);
                }
                l--;
                r++;
            }
        }
        return maxString;
    }
    string naiveApproach(string &s){
        int n = s.length();
        string maxString = s.substr(0,1);
        int maxLen = 1;
        for(int i = 0; i < n; i++){
            for(int j = i+maxLen; j < n; j++){
                string temp = s.substr(i,j-i+1);
                if(temp.length()>maxLen && isPalindrome(temp)){
                    maxLen = temp.length();
                    maxString = temp;
                }
            }
        }
        return maxString;
    }
    string expandingAroundCenter(string &s){
        int n = s.length();
        int maxLen = 1;
        string maxString = s.substr(0,1);
        for(int i = 0; i < n; i++){
            //finding for the odd length string
            int l = i, r = i;
            while (l >=0 and r < n and s[l]==s[r]) {
                if(maxLen < r - l +1){
                    maxLen = r - l + 1;
                    maxString = s.substr(l,maxLen);
                }
                l--;
                r++;
            }
            //finding for the even length string
            l = i, r = i+1;
            while (l >=0 and r < n and s[l]==s[r]) {
                if(maxLen < r - l +1){
                    maxLen = r - l + 1;
                    maxString = s.substr(l,maxLen);
                }
                l--;
                r++;
            }
        }
        return maxString;
    }
};

// Attempt = 17th December 2025
class Solution1{
public:
    string longestPalindrome(string s){
        int n = s.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1,0));
        int maxLen = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; i <= n; i++){
                int norm_i = i-1;
                int norm_j = j-1;
                if(s[norm_i]==s[n-1-norm_j]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                    maxLen = max(maxLen, dp[i][j]);
                }else{
                    dp[i][j] = 0;
                }
            }
        }
        return maxLen;
    }
};