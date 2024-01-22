#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        unordered_map<int,int> freq;
        for(int i : nums){
            freq[i]++;
        }
        int count = 0;
        for(auto it: freq){
            int temp = it.second;
            int num1 = it.second / 3;
            it.second %= 3;
            num1 += it.second / 2;
            int num2 = it.second / 2;
            count += min(num1,num2)
        }
        return count;
    }
};