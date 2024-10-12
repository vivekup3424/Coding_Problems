/**
 * Problem Statement: Paint House

You are given an n x 3 cost matrix costs where costs[i][0], costs[i][1], 
and costs[i][2] represent the cost of painting house i with red, blue,
and green, respectively.

    You need to paint all the houses such that no two adjacent 
    houses have the same color.
    Find the minimum cost to paint all the houses.

Constraints:

    1 <= costs.length <= 100
    0 <= costs[i][j] <= 20
*/

#include <bits/stdc++.h>
using namespace std;

int minCostPainHouse(vector<vector<int>> &costs){
    int numHouse = costs.size();
    vector<vector<int>> dp(numHouse, vector<int>(3,0));
    //if I had only one one house, then
    //cost of painting it, would be equal to the cost of painiting it 
    //either red, blue of green
    //
    //hence base case is
    dp[0][0] = costs[0][0], dp[0][1] = costs[0][1], dp[0][2] = costs[0][2];
    for(int i = 1; i < numHouse; i++){
        dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i][1];
        dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0];
        dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2];
    }
    return min({dp[numHouse-1][0], dp[numHouse-1][1], dp[numHouse -1][2]});
}
