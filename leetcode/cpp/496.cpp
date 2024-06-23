// use a temp data member to hold next greater element value and then traverse

#include <bits/stdc++.h>
using namespace std;

//brute force approach 1
class Solution1
{
public:
    vector<int> findNextGreater(vector<int> &nums)
    {
        int n = nums.size();
        int m = -1;
        vector<int> results(n, -1);
        for (int i = n - 1; i >= 0; i--)
        {
            if (m > nums[i])
            {
                results[i] = m;
            }
            if (i != 0 and nums[i] > nums[i - 1])
            {
                m = nums[i];
            }
        }
        return results;
    }
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> results = findNextGreater(nums2);
        unordered_map<int, int> Indices;
        for (int i = 0; i < nums2.size(); i++)
        {
            Indices[nums2[i]] = i;
        }
        vector<int> elements;
        for (int num : nums1)
        {
            elements.push_back(results[Indices[num]]);
        }
        return elements;
    }
};

//Brute force approach 2
class Solution2 {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> m; //stores the index of the numbers
        for(int i = 0;i < nums2.size(); i++){
            m[nums2[i]] = i;
        }
        int n = nums1.size();
        vector<int> ans(n,-1);
        for(int i =0; i < n;i++){
            int currentElement = nums1[i];
            int idx = m[currentElement];
            for(int j = idx + 1; j < nums2.size(); j++){
                if(nums2[j] > currentElement){
                    ans[i] = nums2[j];
                    break;
                }
            }
        }
        return ans;
    }
};

//Better Approach
//Using monotonic stack and a hash-table

/**
 * whenever we see an element x > stack.top()
 * the nextgreater element of the top would be x
*/
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        stack<int> s;
        unordered_map<int, int> m;
        for (int n : nums) {
            while (s.size() && s.top() < n) {
                m[s.top()] = n;
                s.pop();
            }
            s.push(n);
        }
        vector<int> ans;
        for (int n : findNums) ans.push_back(m.count(n) ? m[n] : -1);
        return ans;
    }
};
int main()
{
    vector<int> nums = {1, 2, 3, 4};
    Solution A = Solution();
    vector<int> resuls = A.findNextGreater(nums);
    return 0;
}