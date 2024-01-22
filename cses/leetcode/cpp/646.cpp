#include <bits/stdc++.h>
using namespace std;

class Solution1 {
public:
    //Method 1: Greedy Solution
    bool comparator(vector<int> a, vector<int> b){
        return a[1] < b[1];
    }
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end());
        int endTime = pairs[1][1];
        int count = 1;
        for(int i = 1;i < pairs.size();i++){
            if(pairs[i][0] > endTime){
                count++;
                endTime = pairs[i][1];
            }
        }    
        return count;
    }
};
class Solution2{
    public:
    bool comparator(vector<int> A,vector<int> B){
        return A[1] < B[1]; //ascending order
    }
    int findLongestChain(vector<vector<int>>&pairs){
        int n  = pairs.size();
        sort(pairs.begin(), pairs.end());
        vector<int> dp(n, 1);
        for(int i = 1; i< n; i++){
            dp[i] = max(dp[i], dp[])
        }
    }
};

int main(){
    
}

