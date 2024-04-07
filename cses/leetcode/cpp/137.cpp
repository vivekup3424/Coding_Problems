#include <bits/stdc++.h>
using namespace std;
class Solution{
    //Method 1
    public:
    int singleNumber(vector<int> &nums){
        int ans = 0;
        for(int i = 0; i < 31; i++){
           int count = 0;
           for (int n : nums)
           {
            if(n & 1<<i )count++;
           }
           if (count%3==1)
           {
            ans |= (1<<i);
            count = 0;
           }
        }
        return ans;
    }
    //Time complexity = O(32*N)
    //Space Complexity = O(1)
    //but unfortunately this works only for non-negative integers
};

class Solution2{
    //Method 2
    public:
    int singleNumber(vector<int> &nums){
        sort(nums.begin(),nums.end());
        for(int i = 1; i <nums.size(); i+=3){
            if(nums[i]!=nums[i-1]){
                return nums[i-1];
            }
        }
        return nums.back();
        //in hindsight this solution is way better than the above code
        //because logn <= 32
    }
};
class Solution3{
    //based on the concept of bucket sort
    public:
    int singleNumber(vector<int> &nums){
        
    }
}
int main()
{
    vector<int> v = {1,1,1,3,4,4,4,6,6,6};
    Solution *A = new Solution();
    cout<<A->singleNumber(v)<<endl;
    
}