#include <bits/stdc++.h>
using namespace std;
class Solution{
    bool isIncreasingSubarray(vector<int> &v, int start, int end){
        int prevElement = v[start];
        for(int i = start+1; i < end; i++){
            if(prevElement>=v[i])return false;
            else prevElement = v[i];
        }
        return true;
    }
    int longestAdjacentIncreasingSubarrayLength(vector<int> v){
        int i = 0, j = 1;
    }
};