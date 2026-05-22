import java.util.*;
public class KthLargest {
    private PriorityQueue<Integer> minHeap;
    public KthLargest(int k, int[] nums){
        minHeap = new PriorityQueue<>();
        for (int i = 0; i < nums.length; i++) {
            minHeap.add(nums[i]);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }
    }
    public int add(int val){
        minHeap.add(val);
        if (minHeap.size() > k) {
            minHeap.poll();
        }
        minHeap.peek();
    }
}
