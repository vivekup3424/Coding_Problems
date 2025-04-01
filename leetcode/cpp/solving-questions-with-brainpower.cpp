#include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
    long long mostPoints(vector<vector<int>> &questions){
        return recurse(questions,0);
    }
    long long recurse(vector<vector<int>> &questions, int i){
        int n = questions.size();
        if(i >= n){
            return 0;
        }else{
            int points = questions[i][0];
            int brainpower = questions[i][1];
            return max(points+recurse(questions,i+brainpower+1),recurse(questions,i+1));
        }
    }
    long long mostPointsMemoized(vector<vector<int>> &questions){
        int n = questions.size();
        vector<long long> memo(n,-1);
        return memoized(questions,memo,0);
    }
    long long memoized(vector<vector<int>> &questions, vector<long long> &memo, int i){
        int n = questions.size();
        if(i >= n){
            return 0;
        }
        else if(memo[i]!=-1){
            return memo[i];
        }else{
            int points = questions[i][0];
            int brainpower = questions[i][1];
            return memo[i] = max(points+memoized(questions,memo,i+brainpower+1), memoized(questions,memo,i+1));
        }
    }
    long long mostPointsDp(vector<vector<int>> &questions){
        int n = questions.size();
        vector<long long> dp(n,-1);
        for(int i = n-1; i >= 0; i--){
            int points = questions[i][0];
            int brainPower = questions[i][1];
            long long choiceFirst = points; //choosing
            int nextQuestionIndex = i + brainPower + 1;
            if(nextQuestionIndex<n){
                choiceFirst += dp[nextQuestionIndex];
            }
            long long choiceSecond = 0; //not choosing
            nextQuestionIndex = i+1;
            if(nextQuestionIndex<n){
                choiceSecond += dp[nextQuestionIndex];
            }
            dp[i] = max(choiceFirst, choiceSecond);
        }
        return dp[0];
    }
};