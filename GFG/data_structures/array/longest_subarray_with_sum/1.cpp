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
    //Time complexity = O(n^3)
    //Space Complexity = O(n)
}

//Better way
int getLongestSubarray2(vector<int> &a, long long k){
    int n = a.size();
    int length = 0;
    for(int i = 0;i < n;i++){
        long long sum = 0;
        for(int j = i;j < n;j++){
            sum += a[j];
            if(sum == k){
                length = max(length, j - i + 1); 
            }
        }
    }
    return length;
    //Time Complexity = O(n^2)
    //Space Complexity = O(n)
}

//Optimal way using hashing
//only for postive values inside the array
int getLongestSubarray3(vector<int> &a, long long k){
    unordered_map<int,int> preSumMap; //sum to index mapping
    long long sum = 0;
    int maxLength = 0;
    for(int i = 0;i < a.size(); i++){
        sum += a[i];
        if(sum == k){
            maxLength = i + 1;
        }
        int remaining = sum - k;
        if(preSumMap.find(remaining) != preSumMap.end(){
            int len = i - preSumMap[remaining];
            maxLen = max(maxLen, len);
        })
        preSumMap[sum] = i;
    }
    return maxLength;
}

//optimal with values of array including zero
int getLongestSubarray4(vector<int> &a, long long k){
    unordered_map<int,int> preSumMap; //sum to index mapping
    long long sum = 0;
    int maxLength = 0;
    for(int i = 0;i < a.size(); i++){
        sum += a[i];
        if(sum == k){
            maxLength = i + 1;
        }
        long long remaining = sum - k;
        if(preSumMap.find(remaining) != preSumMap.end(){
            int len = i - preSumMap[remaining];
            maxLen = max(maxLen, len);
        })
        //if sum already doesnt exist, then only update it
        if(preSumMap.find(sum) == preSumMap.end()){
            preSumMap[sum] = i;
        }
    }
    return maxLength;
    //this code is optimal for array containing integers of all types of values
    //time complexity = O(n * logn)
    //space complexity = O(n)
}

int getSmallestSubarraySumK(vector<int> &arr, long long k){
    unordered_map<int,int> prefSumMap;
    int n = arr.size();
    long long sum = 0;
    int minLength = INT_MAX;
    for(int i = 0;i < n;i++){
        sum += arr[i];
        if(sum == k){
            minLength = min(minLength, i+1);
        }
        int remaining = sum - k;
        if(prefSumMap.find(remaining) != prefSumMap.end(){
            int len = i - prefSumMap[remaining];
            maxLen = max(maxLen, len);
        })
        prefSumMap[sum] = i;
    }
    //Best Time Complexity = O(N)
    //Worst Time Complexity = O(N*N)
}