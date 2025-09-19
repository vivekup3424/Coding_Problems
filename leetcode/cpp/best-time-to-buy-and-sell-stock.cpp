#include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
    int maxProfit(vector<int> &prices){
        int currentProfit = 0, maxProfit = 0;
        for(int i = 1; i < prices.size();i++){
            currentProfit+=(prices[i]-prices[i-1]);
            if(currentProfit<0){
                currentProfit = 0;
            }
            maxProfit = max(maxProfit,currentProfit);
        }
        return maxProfit;
    }
};