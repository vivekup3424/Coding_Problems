#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    int numRabbits(vector<int> &answers){
        int total_rabbits = answers.size();
        vector<int> numberIncludingCurrent(total_rabbits+1,0);
        for(int i = 0; i < total_rabbits; i++){
            numberIncludingCurrent[i] = answers[i]+1;
        }
        //calculating frequency of each element
        map<int,int> freq;
        for(int num : numberIncludingCurrent){
            freq[num]+=1;
        }
        int total = 0;
        for(auto it : freq){
            int extra = (it.second)%(it.first);
            total += ((it.second)/(it.first) + (extra != 0)) * (it.first);
        }
        return total;
    }
};
