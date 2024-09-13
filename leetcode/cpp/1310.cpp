#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size(), m = queries.size();
        vector<int> pref(n,0);
        for(int i = 0; i < n; i++){
            if(i==0){
                pref[i] = arr[i];
            }
            else{
                pref[i] = pref[i-1] ^ arr[i];
            }
        }
        vector<int> ans;
        for(auto q: queries){
            int l = q[0], r = q[1];
            if(l==0){
               ans.push_back(pref[r]);
            }
            else{
                ans.push_back(pref[r] ^ pref[l-1]);
            }
        }
        return ans;
    }
};
