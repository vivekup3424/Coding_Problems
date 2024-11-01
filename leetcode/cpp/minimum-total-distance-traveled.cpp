#include <bits/stdc++.h>
#include <cstring>
using namespace std;

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(),robot.end());
        vector<int> smallFactory;
        for(auto f : factory){
            auto position = f[0],limit = f[1];
            while(limit--){
                smallFactory.push_back(position);
            }
        }
        int numRobots = robot.size(), numSmall = smallFactory.size();
        int dp[numRobots+1][numSmall+1];
        memset(dp, INT_MAX, (numRobots+1)*(numSmall+1));
        for(int i = 0; i <= numRobots; i++){
            for(int j = 0; j <= numSmall; j++){
                if(j==0){
                    dp[i][j] = INT_MAX;
                }
                else if(i==0){
                    dp[i][j] = 0;
                }
                else{
                    dp[i][j] = 
                }
            }
        }
    }
};
