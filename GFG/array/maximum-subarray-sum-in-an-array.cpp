#include <bits/stdc++.h>
using namespace std;
vector<int> maxSubarraySum(vector<int> v){
    int currentSum = 0, maxSum = 0;
    int currentStart = -1, currentLength = -1;
    int maxStart = -1, maxLength = -1;
    for (int i = 0; i < v.size(); i++) {
        currentSum += v[i];
        if(currentSum<0){
            currentSum = 0;
            currentStart = i+1;
            currentLength = 1;
        }
        currentLength++;
        if()
    }
}
int main (int argc, char *argv[]) {
    
    return 0;
}
