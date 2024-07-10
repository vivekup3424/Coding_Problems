#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//first let's try writing the recusive approach
//we can have 3 states for each day
//1. Present
//2. Absent
//3. Late

//we can have 2 variables to keep track of the number of days we have been absent and the number of days we have been late consecutively
void recurse(int n, int absent, int late, int i, int &count){
    if(i==n){
        if(absent<=1 && late<=2){
            count++;
        }
    }
    else{
        recurse(n,absent+1,0,i+1,count); //getting absent today
        recurse(n,absent,late+1,i+1,count); //getting late today
        recurse(n,absent,0,i+1,count); //getting present today
    }
}
//building upon the recursive solution, I can make a memoization from it
//for this I need to think of its dimension
//clearly I can think of making it a 3D-dp, but let's see

class Solution {
public:
    int checkRecord(int n) {
        int count = 0;
        
        recurse(n,0,0,0,count);
        return count;
    }
}