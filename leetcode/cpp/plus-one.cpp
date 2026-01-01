#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    vector<int> plusOne(vector<int> &digits){
        int carry = 1;
        vector<int> answer;
        for(int i = digits.size()-1;i>=0;i--){
            int current = digits[i];
            int value = current+carry;
            carry = value / 10;
            value = value % 10;
            answer.push_back(value);
        }
        if(carry!=0){
            answer.push_back(carry);
        }
        reverse(answer.begin(),answer.end());
        return answer;
    }
};