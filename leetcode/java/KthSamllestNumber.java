import java.util.PriorityQueue;

public class KthSamllestNumber {
    //create a maxHeap of size k, 
    //go over the array and keep on adding element one by one
    //as soon as after adding an element, the size of heap is greater than k remove the greatest element from it
    //after the for loop you would be left out with the kth smallest element at the top

    public int kthSmallest(int[] arr, int k){
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a,b) -> b-a);
        for(int i : arr){
            maxHeap.add(i);
            if(maxHeap.size()>k){
                maxHeap.poll();
            }
        }
        return maxHeap.poll();
    }
    
}
