#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        stack<int> stk;
        for(int i = 0; i < n; i++){
            int currentElement  = nums[i];
            if(stk.empty() or stk.top() < nums[i]){
                stk.push(currentElement);
            }
            else{
                stack<int> temp;
                while(stk.size()>0 and stk.top() - currentElement > 0 and stk.top() - currentElement <= limit){ 
                    temp.push(stk.top());
                    stk.pop();
                }
                stk.push(currentElement);
                while(temp.size() > 0){
                    stk.push(temp.top());
                    temp.pop();
                }
            }
        }
        vector<int> answer;
        while(stk.size() > 0){
            answer.push_back(stk.top());
            stk.pop();
        }
        return answer;
    }
};