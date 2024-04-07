#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    //Method 1: Maintaing a frequency hashset
    vector<int> singleNumber1(vector<int>& nums) {
        map<int,int> freq;
        for(int n :nums){
            freq[n]++;
        }
        vector<int> v;
        for(auto it: freq){
            if(it.second==1){
                v.push_back(it.first);
            }
        }
        return v;
    }
};
int main()
{

}