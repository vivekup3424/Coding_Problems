#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int a1=0,a2=0,b1=0,b2=0;
        for(int i = 0; i < n-1; i++){
            a1 = max(a1,nums1[i]);
            b1 = max(b1,nums2[i]);
        }
        a2 = nums1.back();
        b2 = nums2.back();
        if(a1<=a2 and b1<=b2){
            return 0;
        }
        else if(a1<=b2 and b1<=a2){
            return 1;
        }
        return -1;
    }
};