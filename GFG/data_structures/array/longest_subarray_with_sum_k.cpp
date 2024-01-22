#include <bits/stdc++.h>
using namespace std;

//Brute force
int getLongestSubarray1(vector<int> &a, long long k){
    int n = a.size();
    int len = 0;
    for(int i = 0;i < n;i++){//starting index 
        for(int j = 0;j < n;j++){ //ending index
            int sum = 0;
            for(int k = i;k < j;k++){
                sum += a[k];
            }
            if(sum == k){
                len = max(len, j - i + 1);
            }
        }
    }
}