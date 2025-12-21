#include <bits/stdc++.h>
using namespace std;

class Solution{
    private:
    bool isColumnSorted(vector<string> &strs, int columnIdx){
        for(int j = 1; j< strs.size(); j++){
            if(strs[j][columnIdx]<strs[j-1][columnIdx]){
                return false;
            }
        }
        return true;
    }
    public:
    int minDeletionSize(vector<string> &strs){
        int columnSize = strs[0].length();
        int countColumn = 0;
        for(int i = 0; i < columnSize; i++){
            if(!isColumnSorted(strs,i)) countColumn+=1;
        }
        return countColumn;
    }
};