#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        vector<int> suffixMin(n,arr.back());
        vector<int> prefixMax(n,arr.front());
        for(int i = n-1;i >= 0; i--){
            suffixMin[i] = min(arr[i],suffixMin[i+1]);
        }
        for(int i = 0; i < n; i++){
            prefixMax[i] = max(arr[i],prefixMax[i-1]);
        }
        int count = 0;
        for(int i = 0; i < n-1; i++){
            if(prefixMax[i] <= suffixMin[i+1]){
                count++;
            }
        }
        return count+1;
    }
};
