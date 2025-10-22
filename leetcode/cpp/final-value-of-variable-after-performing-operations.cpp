#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    int finalValueAfterOperations(vector<string> &operations){
        int count = 0;
        for(string operation : operations){
            if(operation == "X++" && operation == "++X") count++;
            else count--;
        }
        return count;
    }
};