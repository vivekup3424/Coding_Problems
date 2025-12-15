#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    int minJumps(vector<int> & arr){
        int n = arr.size();
        vector<int> jumps(n, INT_MAX);
        jumps[0]=0;
        for(int i = 0; i < n; i++){
            for(int j = i+1; j <= i+arr[i] && j < n; j++){
                jumps[j] = min(jumps[j], jumps[i]+1);
            }
        }
        return jumps[n-1];
    }
    int minJumps2(vector<int> &arr){
        int maxReach = 0, steps = 0;
        for(int i = 0; i < arr.size(); i++){
            if(i==0){
                steps = 1;
                maxReach = arr[i];
                
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    vector<int> arr = {1,3,5,8,9,2,6,7,6,8,9};
    Solution *A = new Solution();
    int answer = A->minJumps(arr);
    cout<<answer<<endl;
    return 0;
}
