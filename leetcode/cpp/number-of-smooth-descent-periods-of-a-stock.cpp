#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        long long totalCount = 1, currentLength = 1;
        for(int i = 1; i < prices.size(); i++){
            bool isSmoothDescent = (prices[i]+1 == prices[i-1]);
            currentLength = currentLength * isSmoothDescent + 1;
            totalCount += currentLength;
        }
        return totalCount;
    }
};