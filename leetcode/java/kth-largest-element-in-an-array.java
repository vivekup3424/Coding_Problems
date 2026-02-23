import java.util.PriorityQueue;

class Solution {
    public int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for (int i = 0; i < nums.length; i++) {
            minHeap.add(nums[i]);
            if(minHeap.size()>k){
                minHeap.poll();
            }
        }
        return minHeap.poll();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();

        int[] nums1 = {3, 2, 1, 5, 6, 4};
        System.out.println(sol.findKthLargest(nums1, 2));  // Expected: 5

        int[] nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
        System.out.println(sol.findKthLargest(nums2, 4));  // Expected: 4
    }
}