#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    void sort012(vector<int>& arr) {
        int i = 0, j = 0, l = arr.size();
        while(j<l){
            if(arr[j]==0){
                swap(arr[i], arr[j]);
                i++;
                j++;
            }else if(arr[j]==1){
                j++;
            }else{
                l--;
                swap(arr[j], arr[l]);
            }
        }
    }
};