#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    int maxWater(vector<int> &arr) {
        int n = arr.size();
        //maxheights from left
        vector<int> leftMaxHeight(n,arr[0]);
        vector<int> rightMaxHeight(n,arr[n-1]);
        for(int i = 1; i < n; i++){
            leftMaxHeight[i] = max(leftMaxHeight[i-1], arr[i]);
        }
        for(int i = n - 2; i >= 0; i--){
            rightMaxHeight[i] = max(rightMaxHeight[i+1],arr[i]);
        }
        int sum = 0;
        for(int i =0; i < n; i++){
            sum += min(leftMaxHeight[i], rightMaxHeight[i]) - arr[i];
        }
        return sum;
    }
};
