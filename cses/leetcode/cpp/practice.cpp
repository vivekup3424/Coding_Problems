#include <bits/stdc++.h>
using namespace std;

class Solution{
    private:
    bool findSubset(int tasks[],int n, int idx, int leftout_sum){
        if(leftout_sum==0)return true;
        else if(idx>=n and leftout_sum != 0)return false;
        else if(leftout_sum < tasks[idx]) return findSubset(tasks,n,idx+1,leftout_sum);
        return findSubset(tasks,n, idx+1, leftout_sum - tasks[idx]) || findSubset(tasks, n, idx+1, leftout_sum);
    }
    public:
	int minDifference(int tasks[], int n)  { 
	    int sum  = 0;
        for(int i = 0;i < n;i++){
            sum += tasks[i];
        }
        bool result = false;
        int s1 = (sum + 1)/2;
        while(result == false){
            result = findSubset(tasks,n,0,s1);
            s1--;
        }
        return sum - (2 * s1);
	} 

};
