#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;
class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        sort(items.begin(),items.end());
        int maxBeauty = items[0][1];
        for(int i = 0; i < items.size(); i++){
            if(items[i][1]>maxBeauty){
                maxBeauty = items[i][1];
            }
            items[i][1] = maxBeauty;
        }
        vector<int> ans;
        for(int i = 0; i < queries.size(); i++){
            auto q = queries[i];
            //find the highest beauty with price <= q
            int l = 0, r = items.size()-1;
            int maxPrice = 0;
            while(l<=r){
                int mid = (l+r)/2;
                if(items[mid][0]>q){
                    //mid price > given price
                    //go left
                    r = mid-1;
                }else{
                    //find the upper bound
                    l = mid+1;
                    maxPrice = items[mid][1];
                }
            }
            ans.push_back(maxPrice);
        }
        return ans;
    }
};
