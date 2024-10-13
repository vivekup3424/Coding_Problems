#include <bits/stdc++.h>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size();
        int maxi = INT_MIN;
        for(auto v : nums){
            for(auto i : v){
                maxi = max(maxi,i);
            }
        }
        vector<int> hashmap(maxi+1,0);
        for(int i = 0 ; i < n; i++){
            for(int j = 0; j < nums[n].size(); j++){
                hashmap[nums[n][j]] = i;
            }
        }
        int minlen = INT_MAX, minstart = -1;
        int start = 0, end = 0;
        map<int,int> window;
        int counter = 0;
        while(end < hashmap.size()){
            window[hashmap[end]]++;
            if(window[hashmap[end]]==1){
                counter++;
            }
            while(counter>=n){
                int currentlength = end - start + 1;
                if(currentlength<minlen){
                    minlen = currentlength;
                    minstart = start;
                }
                window[hashmap[start]]--;
                if(window[hashmap[start]] == 0){
                    counter--;
                }
                start++;
            }
        }
        return {minstart, minstart + minlen -1};
    }
};
