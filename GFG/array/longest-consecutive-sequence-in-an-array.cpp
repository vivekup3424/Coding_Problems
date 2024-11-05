/*
 *Problem Statement: You are given an array of ‘N’ integers. You need to find 
 the length of the longest sequence which contains the consecutive 
 elements.*/
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int longestConsecutiveArray(vector<int> v){
    unordered_set<int> st;
    unordered_map<int, int> freq;
    for(auto num : v){
        st.insert(num);
    }
    for(auto num : v){
        if(st.count(num-1)){
            freq[num]++; //adding current element
            freq[num-1] = freq[num]+1;
        }
    }
}
