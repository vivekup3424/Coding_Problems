#include <bits/stdc++.h>
using namespace std;

struct job{
    int startTime;
    int endTime;
    int profit;
};
class Solution {
public:
    bool comparator(struct job *A, struct job*B){
        return A->startTime < B->startTime;
        //sort in ascending order
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<struct job> jobs;
        for(int i = 0; i < n;i++){
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());
        
    }
};

int main(){

}