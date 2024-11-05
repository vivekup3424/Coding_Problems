#include <bits/stdc++.h>
using namespace std;

//Problem 1. Given a binary stream, count the maximum length of consecutive ones
int maxConsecutiveOnes(vector<bool> &v){
    int maxFreq = 0, currentFreq = 0;
    for(auto i : v){
        if(i){
            currentFreq++;
        }else{
            currentFreq = 0;
        }

        if(currentFreq>maxFreq){
            maxFreq = currentFreq;
        }
    }
    return maxFreq;
}

//Problem 2. 
