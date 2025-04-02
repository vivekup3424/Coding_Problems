import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

public class MinHeapPractice {
    public static void main(String[] args) {
        Queue<Integer> minHeap = new PriorityQueue<>();
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Please enter the length of minHeap:\t");
        int length = scanner.nextInt();
        
        for(int i = 0; i < length; i++){
            System.out.println("Enter the value of the integer:\t");
            int num = scanner.nextInt();
            minHeap.add(num);
            System.out.println("new minheap = " + minHeap);
        }
        
        scanner.close();
    }    
}