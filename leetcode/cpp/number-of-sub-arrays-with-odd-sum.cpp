#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    int numOfSubarrays(vector<int> &arr){
        int length = arr.size();
        int cumulativeSum = 0;
        int num_even = 1;
        int num_odd = 0;
        int num_odd_subarrays = 0;
        for(int i = 0; i < length; i++){
            cumulativeSum += arr[i];
            if(cumulativeSum%2==0){
                num_odd_subarrays += num_odd;
            }else{
                num_odd_subarrays += num_even;
            }

            if(cumulativeSum%2==0){
                num_even+=1;
            }else{
                num_odd+=1;
            }
        }
        return num_odd_subarrays;
    }
};
int main(){
    vector<int> v = {1,2,3,4,5,6,7};
    auto A = new Solution();
    cout<<A->numOfSubarrays(v)<<endl;
}