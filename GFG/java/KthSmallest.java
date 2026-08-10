import java.util.*;

class Solution{
    public int kthSmallest(int[] arr, int k){
        int n = arr.length;
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a,b)->b-a);
        for(int i = 0; i < n; i++){
            maxHeap.add(arr[i]);
            if(maxHeap.size()>k){
                maxHeap.poll();
            }
        }
        return maxHeap.poll();
    }
}