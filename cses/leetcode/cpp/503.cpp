#include <bits/stdc++.h>
using namespace std;

//brute force approach using two for loops in order to search for next greater element
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n,-1);
        int maxValue = *max_element(nums.begin(),nums.end());
        for(int i = 0;i < n;i++){
            int currentValue = nums[i];
            if(currentValue == maxValue){
                ans[i] = -1;
                continue;
            }
            for(int j = i; true; j = (j + 1)%n){
                if(nums[j]>currentValue){
                    ans[i] =  nums[j];
                    break;
                }
            }
        }
        return ans;
    }
    //Time complexity = O(n^2)
    //Space complexity = O(n) because we are using a vector for n
};

//better approach using monotonic stream
int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            std::cin >> nums[i];
        }

        // Create an instance of the solution class
        Solution solution;

        // Call the function and get the result
        std::vector<int> result = solution.nextGreaterElements(nums);

        // Print the result
        for (int i : result) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}