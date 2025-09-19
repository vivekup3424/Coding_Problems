#include <bits/stdc++.h>
using namespace std;
class Solution{
    public:
    int findDuplicate(vector<int> &nums){
        int sum = accumulate(nums.begin(), nums.end(),0);
        cerr<<"sum = "<<sum<<endl;
        int n = nums.size() - 1;
        int expected_sum = n * (n + 1) / 2;
        return sum - expected_sum;
    }
};