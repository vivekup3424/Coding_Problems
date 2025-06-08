#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // returns the index where pivot element is going to be inside the sorted array
    int partition(vector<int> &nums, int left, int right)
    {
        int pivot_index = right;
        int pivot = nums[pivot_index];
        int j = left; // j is for elements greater than or equal to the pivot
        for (int i = left; i < right; i++)
        {
            if (nums[i] >= pivot)
            {
                swap(nums[i], nums[j]);
                j++;
            }
        }
        swap(nums[j], nums[pivot_index]);
        return j;
    }
    void quicksortInDescendingOrder(vector<int> &nums, int left, int right)
    {
        if (left < right)
        {
            int pivotIndex = partition(nums, left, right);
            quicksortInDescendingOrder(nums, left, pivotIndex - 1);
            quicksortInDescendingOrder(nums, pivotIndex + 1, right);
        }
    }
    int findKthLargestByQuickSort(vector<int> &nums, int k)
    {
        quicksortInDescendingOrder(nums, 0, nums.size() - 1);
        return nums[k - 1];
    }

    int findKthLargestByMinHeap(vector<int> &nums, int k)
    {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int num : nums)
        {
            minHeap.push(num);
            if (minHeap.size() > k)
            {
                minHeap.pop();
            }
        }
        return minHeap.top();
        // Time complexity = O(N*logK)
    }

    int partitionForQuickSelect(vector<int> &nums, int left, int right)
    {
        int pivot_index = right;
        int j = left; //stores the element greater or equal to pivot
        for (int i = left; i < right; i++){
            if(nums[i]>=nums[pivot_index]){
                swap(nums[i],nums[j]);
                j++;
            }
        }
        swap(nums[j],nums[pivot_index]);
        return j; //place where the pivot is supposed to go after sorting
    }
    int quickSelect(vector<int> &nums, int k, int left, int right){
        if(left==right){
            return nums[left];
        }
        int pivotIndex = partitionForQuickSelect(nums, left, right);
        if(pivotIndex==k){
            return nums[k];
        }else if(k < pivotIndex){
            return quickSelect(nums, k, left,pivotIndex-1);
        }else{
            return quickSelect(nums, k, pivotIndex+1, right);
        }
    }
    int findKthLargestByQuickSelect(vector<int> &nums, int k)
    {
        return quickSelect(nums,k-1,0,nums.size()-1);
    }
};