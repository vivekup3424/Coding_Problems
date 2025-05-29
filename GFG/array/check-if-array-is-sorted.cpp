#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    bool checkIfSorted(vector<int> &arr){
        for(int i =1; i < arr.size(); i++){
            if(arr[i]<arr[i-1]){
                return false;
            }
        }
        return true;
    }
};