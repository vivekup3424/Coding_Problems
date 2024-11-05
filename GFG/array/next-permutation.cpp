#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
public:
    bool nextPermutation(vector<int>& nums) {
        int j = nums.size()-1;
        while(j > 0){
            for(int i = j-1; i >= 0; i--){
                if(nums[i]<nums[j]){
                    swap(nums[i],nums[j]);
                    return true;
                }
            }
            j--;
        }
        return false;
    }
};
int main (int argc, char *argv[]) {
    cout<<"Enter the length of the array:-\t";
    int n;
    cin>>n;
    cout<<"Enter the elements of the array:-\n";
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin>>v[i];
    }
    Solution().nextPermutation(v);
    cout<<"Next Permutation:-\n";
    for(auto i : v){
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}
